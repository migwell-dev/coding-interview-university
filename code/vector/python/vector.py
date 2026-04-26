from typing import Generic, TypeVar

T = TypeVar("T")

class Vector(Generic[T]):
    def __init__(self):
        self._capacity: int = 2
        self._length: int = 0
        self._data: list[T | None] = [None] * self._capacity

    def size(self) -> int:
        return self._length

    def capacity(self) -> int:
        return self._capacity

    def is_empty(self) -> bool:
        return self._length == 0

    def resize(self) -> None:
        if (self._length >= self._capacity):
            self.grow()
        elif (self._length > 0 and self._length <= self._capacity // 4):
            self.shrink()
        else:
            pass

    def grow(self):
        if self._capacity == 0:
            self._capacity = 2
        else:
            self._capacity *= 2

        new_data: list[T | None] = [None] * self._capacity

        for i in range(self._length):
            new_data[i] = self._data[i]

        self._data = new_data

    def shrink(self):
        self._capacity //= 2

        new_data: list[T | None] = [None] * self._capacity

        for i in range(self._length):
            new_data[i] = self._data[i]

        self._data = new_data

    def at(self, index: int) -> T | None:
        assert 0 <= index < self._length, "Index out of bounds"
        return self._data[index]

    def push(self, item: T) -> None:
        self.resize()
        self._data[self._length] = item
        self._length += 1

    def insert(self, index: int, item: T) -> None:
        assert 0 <= index < self._length, "Index out of bounds"

        self.resize()

        for i in range(self._length, index ,-1):
            self._data[i] = self._data[i-1]

        self._data[index] = item
        self._length += 1

    def prepend(self, item: T) -> None:
        self.insert(0, item)

    def pop(self) -> T | None:
        assert not self.is_empty(), "Vector is empty"
        res = self._data[self._length-1]
        self._length -= 1
        self.resize()
        return res

    def delete(self, index: int) -> None:
        assert 0 <= index < self._length, "Index out of bounds"

        for i in range(index, self._length-1, 1):
            self._data[i] = self._data[i+1]

        self._length -= 1
        self.resize()

    def remove(self, item: T) -> None:
        for i in range(self._length):
            if self._data[i] == item:
                self.delete(i)
                return

    def find(self, item: T) -> int:
        for i in range(self._length):
            if self._data[i] == item:
                return i
        return -1
