from typing import Iterable, Any
from math import log2, floor
import sys

_base_depth = 1000


class Heap:

    # basicly, it's min heap
    def __init__(self, collection: Iterable[Any], _max=False, _max_depth=1000):
        if _max_depth != _base_depth:
            sys.setrecursionlimit(_max_depth)  # to sift heap

        # min heap (_max=False):
        # parent <= children

        # max heap (_max=True):
        # parent >= children

        self.__max = _max
        self.__heap = list(collection)

        depth = self.get_depth()

        if depth == 0:
            return

        # build heap
        max_index = 2 ** (depth - 2)  # depth - 2 is penultimate layer
        for cur_index in range(max_index, -1, -1):
            self.__sift_down(cur_index)

    def __sift_down(self, index: int) -> None:
        # max-heap and min-heap versions requires different conditions

        next_index = -1

        # if left child exist
        if index * 2 + 1 < len(self):
            # if heap isnt so heap
            if not self.__max and self.__heap[index * 2 + 1] < self.__heap[index] or \
                    self.__max and self.__heap[index * 2 + 1] > self.__heap[index]:
                next_index = index * 2 + 1

        # if right child exist
        if index * 2 + 2 < len(self):
            # if heap isnt so heap
            if not self.__max and self.__heap[index * 2 + 2] < self.__heap[index] or \
                    self.__max and self.__heap[index * 2 + 2] > self.__heap[index]:
                # if left child is good
                if next_index == -1:
                    next_index = index * 2 + 2
                else:
                    # here we need to choose the best child to switch
                    if not self.__max:
                        if self.__heap[index * 2 + 1] < self.__heap[index * 2 + 2]:
                            next_index = index * 2 + 1
                        else:
                            next_index = index * 2 + 2
                    if self.__max:
                        if self.__heap[index * 2 + 1] > self.__heap[index * 2 + 2]:
                            next_index = index * 2 + 1
                        else:
                            next_index = index * 2 + 2

        # if all right
        if next_index == -1:
            return

        self.__heap[index], self.__heap[next_index] = self.__heap[next_index], self.__heap[index]
        self.__sift_down(next_index)

    def __sift_up(self, index: int) -> None:
        # if root
        if index == 0:
            return

        # if current item is right child
        if index % 2 == 0:
            parent = (index - 2) // 2
        # if current item is left child
        else:
            parent = (index - 1) // 2

        if not self.__max and self.__heap[parent] > self.__heap[index] or self.__max and self.__heap[parent] < \
                self.__heap[index]:
            self.__heap[parent], self.__heap[index] = self.__heap[index], self.__heap[parent]
            self.__sift_up(parent)

    def add(self, item: Any) -> None:
        self.__heap.append(item)
        self.__sift_up(len(self) - 1)

    # wtf somebody really deletes items from heap??
    # actually i hope that this works how it must work
    def remove(self, key: Any) -> None:
        index = -1
        for i in range(len(self)):
            if self.__heap[i] == key:
                index = i
                break

        if index == -1:
            raise KeyError(f"Element {key} doesn't exist in heap!")

        self.__heap[index], self.__heap[len(self) - 1] = self.__heap[len(self) - 1], self.__heap[index]
        del self.__heap[len(self) - 1]
        self.__sift_down(index)

    def __delitem__(self, key) -> None:
        self.remove(key)

    def __pop(self) -> Any:
        res = self.__heap[0]

        self.__heap[0], self.__heap[len(self) - 1] = self.__heap[len(self) - 1], self.__heap[0]
        del self.__heap[len(self) - 1]
        self.__sift_down(0)

        return res

    def pop_max(self) -> Any:
        if not self.__max:
            raise TypeError("This heap isn't max heap!")
        return self.__pop()

    def pop_min(self) -> Any:
        if self.__max:
            raise TypeError("This heap isn't min heap!")

        return self.__pop()

    def get_depth(self) -> int:
        if len(self.__heap) == 0:
            return 0

        # actually idk why i calculate depth of tree like this
        return floor(log2(len(self.__heap))) + 1

    def is_min(self) -> bool:
        return not self.__max

    def is_max(self) -> bool:
        return self.__max

    def __str__(self) -> str:
        # print(self.__heap)
        cur_index = 0
        cur_layer = 0
        _display = []
        depth = self.get_depth()
        # print(depth)

        while cur_layer < depth:
            _temp: list[str] = []
            for _ in range(2 ** cur_layer):
                if cur_index >= len(self):
                    break
                _temp.append(str(self.__heap[cur_index]))
                cur_index += 1

            _display.append(
                ' ' * (depth - cur_layer - 1) + ' '.join(_temp)
            )
            cur_layer += 1
        return '\n'.join(_display)

    def __repr__(self) -> str:
        return f'Heap<{id(self)}>'

    def __len__(self) -> int:
        return len(self.__heap)


def heap_sort(items: Iterable[Any], reverse=False) -> list[Any]:
    heap = Heap(items, _max=reverse)
    sorted_items = []
    for _ in range(len(heap)):
        if not reverse:
            sorted_items.append(heap.pop_min())
        else:
            sorted_items.append(heap.pop_max())
    return sorted_items


# tests
if __name__ == '__main__':
    from random import randrange
    from time import time
    # heap tests:
    heap = Heap([0, 0, 1, 1, 0, 0, 9])
    print(heap)
    del heap[0]
    print()
    print(heap)

    # heap-sort tests:
    array = [1, 7, 4, -1, 5, 1, 2, 3]
    array = heap_sort(array, reverse=True)
    print(array)

    nums = [randrange(1, 10001) for i in range(10000)]
    _nums1 = nums.copy()
    _nums2 = nums.copy()

    start1 = time()
    _nums1 = sorted(_nums1)
    print(f'time for built-in sort: {time() - start1}')

    start2 = time()
    _nums2 = heap_sort(_nums2)
    print(f'time for heap-sort: {time() - start2}')


    #   0
    #  1 2
    # 3 4 5 6
