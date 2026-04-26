import pytest
from vector import Vector  # pyright: ignore[reportImplicitRelativeImport]


def make_vector() -> Vector[int]:
    return Vector()


def test_new_vector_is_empty() -> None:
    v: Vector[int] = make_vector()

    assert v.size() == 0
    assert v.is_empty() is True
    assert v.capacity() >= 1


def test_push_single_element() -> None:
    v: Vector[int] = make_vector()

    v.push(10)

    assert v.size() == 1
    assert v.at(0) == 10


def test_push_multiple_elements() -> None:
    v: Vector[int] = make_vector()

    for i in range(10):
        v.push(i)

    assert v.size() == 10

    for i in range(10):
        assert v.at(i) == i


def test_insert_middle() -> None:
    v: Vector[int] = make_vector()

    v.push(1)
    v.push(2)
    v.push(3)

    v.insert(1, 99)

    assert v.at(0) == 1
    assert v.at(1) == 99
    assert v.at(2) == 2
    assert v.at(3) == 3


def test_pop() -> None:
    v: Vector[int] = make_vector()

    v.push(1)
    v.push(2)
    v.push(3)

    result: int | None = v.pop()

    assert result == 3
    assert v.size() == 2


def test_find() -> None:
    v: Vector[int] = make_vector()

    v.push(10)
    v.push(20)
    v.push(30)

    index: int = v.find(20)

    assert index == 1


def test_remove() -> None:
    v: Vector[int] = make_vector()

    v.push(1)
    v.push(2)
    v.push(3)

    v.remove(2)

    assert v.find(2) == -1
    assert v.size() == 2


def test_delete() -> None:
    v: Vector[int] = make_vector()

    v.push(1)
    v.push(2)
    v.push(3)

    v.delete(1)

    assert v.at(0) == 1
    assert v.at(1) == 3


def test_invalid_access() -> None:
    v: Vector[int] = make_vector()

    with pytest.raises(AssertionError):
        _ = v.at(0)
