class Jar:
    def __init__(self, capacity=12):
        if capacity > 12:
            capacity = 12
        if capacity < 0:
            raise ValueError("Invalid input")
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        self.size += n
        if self.size > self.capacity:
            raise ValueError("Full jar")

    def withdraw(self, n):
        self.size -= n
        if self.size < 0:
            raise ValueError("Empty jar")

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

    @size.setter
    def size(self, n):
        self._size = n

def main():
    jar = Jar()
    print(str(jar.capacity))
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))

main()