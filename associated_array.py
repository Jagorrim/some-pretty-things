from typing import Any, Hashable
from collections.abc import Iterator
from copy import deepcopy


# STRUCTURE OF ITEMS IN __array:
# [
# [0] full hash of key
# [1] key
# [2] value
# ]

class AArray1:
    def __init__(self, max_nested_len: int = 5) -> None:
        self.__set_start()
        if max_nested_len < 5:
            raise ValueError(f'max_nested_len must be greater than or equal to 5')
        self.__max_nested_len = max_nested_len

    def __setitem__(self, key: Hashable, value: Any) -> None:
        full_hash = hash(key)
        scope_hash = full_hash % len(self.__array)

        data = [full_hash, key, value]

        if self.__array[scope_hash] is None:
            self.__array[scope_hash] = []
            self.__array[scope_hash].append(data)
            self.__len += 1
            return

        does_exist = False

        # trying to find item with hash like this and key like this
        for index in range(len(self.__array[scope_hash])):
            # comparison of received key and key in array is requered to avoid collisions
            if self.__array[scope_hash][index][0] == full_hash and \
                    self.__array[scope_hash][index][1] == key:
                does_exist = True
                break

        if does_exist:
            self.__array[scope_hash][index][2] = value
            return

        elif len(self.__array[scope_hash]) < self.__max_nested_len:
            self.__array[scope_hash].append(data)
        else:
            self.__extend(
                self.__get_all_items() + [data]
            )

        self.__len += 1

    def __getitem__(self, key: Hashable) -> Any:
        full_hash = hash(key)
        scope_hash = full_hash % len(self.__array)

        scope = self.__array[scope_hash]

        if scope is None:
            raise KeyError(key)

        for i in scope:
            # comparison of received key and key in array is requered to avoid collisions
            if i[0] == full_hash and key == i[1]:
                return i[2]
        raise KeyError(key)

    def __delitem__(self, key: Hashable) -> None:
        full_hash = hash(key)
        scope_hash = full_hash % len(self.__array)

        scope = self.__array[scope_hash]

        if scope is None:
            raise KeyError(key)

        does_exist = False
        for index in range(len(scope)):
            # comparison of received key and key in array is requered to avoid collisions
            if scope[index][0] == full_hash and scope[index][1] == key:
                does_exist = True
                break

        if does_exist:
            if len(scope) == 1:
                self.__array[scope_hash] = None
            else:
                del scope[index]
            self.__len -= 1
        else:
            raise KeyError(key)

    def __get_all_items(self) -> list[Any]:
        _items = []
        for i in self.__array:
            if i is None:
                continue
            _items.extend(i)

        return _items

    def __set_start(self) -> None:
        self.__len = 0
        self.__array = [None] * 100  # start size of array

    def keys(self) -> Iterator[Any]:
        for i in self.__array:
            if i is None:
                continue
            for j in i:
                yield j[1]  # yield key

    def values(self) -> Iterator[Any]:
        for i in self.__array:
            if i is None:
                continue
            for j in i:
                yield j[2]  # yield value

    def items(self) -> Iterator[tuple[Any, Any]]:
        for i in self.__array:
            if i is None:
                continue
            for j in i:
                yield j[1], j[2]  # yield tuple that contains key and value

    def get(self, key: Hashable, default: Any = None) -> Any | None:
        try:
            value = self.__getitem__(key)
            return value
        except KeyError:
            return default

    def pop(self, key: Hashable) -> Any:
        value = self.__getitem__(key)
        self.__delitem__(key)
        return value

    def popitem(self) -> tuple[Any, Any]:
        if len(self) == 0:
            raise KeyError('popitem(): dictionary is empty')

        found = False
        for i in self.__array:
            if i is None:
                continue

            for j in i:
                key = j[1]
                value = j[2]

                found = True
                break

            if found:
                break

        self.__delitem__(key)
        return key, value

    def setdefault(self, key: Hashable, default: Any = None) -> Any:
        try:
            value = self.__getitem__(key)
            return value

        except KeyError:
            self.__setitem__(key, default)

            return default

    def clear(self) -> None:
        self.__set_start()

    def copy(self) -> "AArray1":
        new = AArray1(max_nested_len=self.__max_nested_len)
        new._AArray1__len = self.__len
        new._AArray1__array = deepcopy(self.__array)
        return new

    def __extend(self, all_items: list[Any]) -> None:
        array = [None] * len(self.__array) * 2
        for item in all_items:
            _hash = item[0] % len(array)
            if array[_hash] is None:
                array[_hash] = []
                array[_hash].append(item)
            else:
                array[_hash].append(item)

    def __len__(self) -> int:
        return self.__len

    def __str__(self) -> str:
        representation = []

        for i in self.__array:
            if i is None:
                continue

            for _, key, value in i:
                representation.append(
                    f'{repr(key)}: {repr(value)}'
                )
        return f'{{{", ".join(representation)}}}'


# tests
if __name__ == '__main__':
    t = AArray1()
    t[1] = [5]
    print(t)
    t2 = t.copy()
    print(t2)
    t[1][0] = 2
    print(t)
    print(t2)
