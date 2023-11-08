import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import pytz
from datetime import datetime
import string

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Create new table, and index (for efficient search later on) to keep track of stock orders, by each user
db.execute(
    "CREATE TABLE IF NOT EXISTS stocks (id INTEGER, user_id NUMERIC NOT NULL, symbol TEXT NOT NULL, \
            shares NUMERIC NOT NULL, price NUMERIC NOT NULL, timestamp TEXT, PRIMARY KEY(id), \
            FOREIGN KEY(user_id) REFERENCES users(id))"
)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "GET":
        # Show username
        user_id = session["user_id"]
        username = db.execute("SELECT username FROM users WHERE id = ?", user_id)[0][
            "username"
        ]
        # Symbol-Shares dictionary ({symbol:shares})
        user_shares = share(user_id)
        total = 0
        for symbol, shares in user_shares.items():
            result = lookup(symbol)
            name = result["name"]
            price = result["price"]
            value = shares * price
            total += value
            user_shares[symbol] = (name, shares, usd(price), usd(value))
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0][
            "cash"
        ]
        total += user_cash
        return render_template(
            "index.html",
            username=username,
            user_shares=user_shares,
            user_cash=usd(user_cash),
            total=usd(total),
        )
    else:
        # Add cash to account
        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0][
            "cash"
        ]
        adding = int(request.form.get("add_cash")) + user_cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", adding, user_id)
        return redirect("/")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Method = "GET"
    if request.method == "GET":
        return render_template("buy.html")
    # Method = "POST"
    else:
        # API
        result = lookup(request.form.get("symbol"))
        # Error handling
        share = request.form.get("shares")
        if result == None:
            return apology("Symbol doesn't exist", 400)

        # Check share is numeric data type
        try:
            share = int(share)
            if share <= 0:
                return apology("INVALID SHARES", 400)
        except ValueError:
            return apology("INVALID SHARES", 400)

        symbol = result["symbol"]
        price = result["price"]

        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        remain = cash - (share * price)
        if remain < 0:
            return apology("Not enough cash", 400)

        # Update databases
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, user_id)
        db.execute(
            "INSERT INTO stocks (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
            user_id,
            symbol,
            share,
            price,
            time_now(),
        )

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    history = db.execute(
        "SELECT symbol, shares, price, timestamp FROM stocks WHERE user_id = ?", user_id
    )
    return render_template("history.html", history=history[::-1])


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash("Login successful!!", "success")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        result = lookup(symbol)
        if result == None:
            return apology("Symbol doesn't exist", 400)
        else:
            return render_template(
                "quoted.html",
                name=result["name"],
                price=usd(result["price"]),
                symbol=result["symbol"],
            )
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # List od users
        users = db.execute("SELECT username FROM users")
        usernames = [user["username"] for user in users]

        # Forms
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Error handling
        if not username or not password or not confirmation:
            return apology("fields required", 400)
        elif username in usernames:
            return apology("user already exist", 400)
        elif password_validation(password) == False:
            return apology("Invalid password", 400)
        elif password != confirmation:
            return apology("password doesn't match", 400)

        # Log the user in
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        user = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = user[0]["id"]
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Method = "GET"
    if request.method == "GET":
        user_id = session["user_id"]
        shares_owned = share(user_id)
        return render_template("sell.html", shares_owned=shares_owned)
    # Method = "POST"
    else:
        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        shares_owned = share(user_id)
        result = lookup(symbol)
        # Error handling
        if symbol not in shares_owned.keys() or shares > shares_owned[symbol]:
            return apology("Not enough shares")
        price = result["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        gain = cash + (shares * price)
        # Update databases
        db.execute("UPDATE users SET cash = ? WHERE id = ?", gain, user_id)
        db.execute(
            "INSERT INTO stocks (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
            user_id,
            symbol,
            -shares,
            price,
            time_now(),
        )

        return redirect("/")


@app.route("/password", methods=["GET", "POST"])
@login_required
def change_password():
    """Change the password"""
    if request.method == "GET":
        return render_template("password.html")
    else:
        user_id = session["user_id"]
        user_password = db.execute("SELECT hash FROM users WHERE id = ?", user_id)[0][
            "hash"
        ]
        current_password = request.form.get("password")

        # Error handling
        # Ensure username exists and password is correct
        if not check_password_hash(user_password, current_password):
            return apology("Invalid password", 403)

        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")

        # Error handling
        if (password_validation(new_password) == False) or (
            new_password != confirmation
        ):
            return apology("Invalid password")

        hash = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", hash, user_id)

        return redirect("/")


@app.route("/delete", methods=["GET", "POST"])
@login_required
def delete():
    """Delete the account"""
    if request.method == "GET":
        return render_template("delete.html")
    else:
        user_id = session["user_id"]
        password = request.form.get("password")
        user_password = db.execute("SELECT hash FROM users WHERE id = ?", user_id)[0][
            "hash"
        ]
        confirmation = request.form.get("confirmation")

        # Confirmation
        if password != confirmation or not check_password_hash(user_password, password):
            return apology("Incorrect password", 400)
        else:
            db.execute("DELETE FROM stocks WHERE user_id = ?", user_id)
            db.execute("DELETE FROM users WHERE id = ?", user_id)
            session.clear()
            return redirect("/login")


# HELPER FUNCTIONS
def time_now():
    """Helper function: Get current GMT date and time"""

    utc_offset = pytz.timezone("Etc/GMT+4")
    now_local = datetime.now(utc_offset)
    return str(now_local.date()) + " @time " + now_local.time().strftime("%H:%M:%S")


def share(user_id):
    """Helper function: Return a dictionary with the symbol and the shares: {symbol:shares}"""

    owns = db.execute("SELECT symbol, shares FROM stocks WHERE user_id = ?", user_id)
    dict = {}
    for i in owns:
        symbol, shares = i["symbol"], i["shares"]
        dict[symbol] = dict.setdefault(symbol, 0) + shares
    # Eliminate all the zero values symbols from the dict
    dict = {i: j for i, j in dict.items() if j != 0}
    return dict


def password_validation(password):
    """Helper function: Return true if the password has at least 8 characters
    where at least one must be a number, one a punctuation and one an uppercase letter
    """

    punctuation = string.punctuation
    for i in password:
        if i.isupper() or i.isdigit() or (i in punctuation) or i.isalpha():
            pass
        else:
            return False
    return True
