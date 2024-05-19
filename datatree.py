from copy import deepcopy
from typing import Iterable
from collections import deque


class DataTree:
    # this is data structure for strings.
    # It's actually scalable to be structure for any collection of hashable elements
    def __init__(self) -> None:
        self.__data = {}
        self.string_count = 0

    def get_tree(self) -> dict:
        # returns deepcopy of tree
        return deepcopy(self.__data)

    def add(self, string: str) -> None:
        # adding new string to tree

        if len(string) == 0:
            raise ValueError('Zero string can not be added to DataTree!')

        cur_level = self.__data

        for letter in string:
            if letter not in cur_level:
                cur_level[letter] = {}
            cur_level = cur_level[letter]

        if 'end_for' not in cur_level:
            cur_level['end_for'] = 0
        cur_level['end_for'] += 1
        self.string_count += 1

    def delete(self, string: str) -> None:
        # deleting string from tree
        levels = [self.__data]
        cur_level = self.__data

        for letter in string:
            if letter not in cur_level:
                raise ValueError(f'Tree {self} does not contain {string}!')

            cur_level = cur_level[letter]
            levels.append(cur_level)

        # if this level is end for many strings
        if 'end_for' in cur_level and cur_level['end_for'] > 1:
            cur_level['end_for'] -= 1
            self.string_count -= 1

        # if this level is end for only one string, but there are strings that longer than it
        elif 'end_for' in cur_level and cur_level['end_for'] == 1 and len(cur_level) > 1:
            del cur_level['end_for']
            self.string_count -= 1

        # if this level is end for only one string and there are no string that longer than it
        elif 'end_for' in cur_level and cur_level['end_for'] == 1 and len(cur_level) == 1:
            end_counter = 0

            for index in range(len(string) - 1, -1, -1):
                if len(levels[index][string[index]]) == 1 \
                        and 'end_for' in levels[index][string[index]] \
                        and end_counter == 0:  # we can not delete more than one string
                    end_counter += 1
                    del levels[index][string[index]]
                elif len(levels[index][string[index]]) == 0:
                    del levels[index][string[index]]
                else:
                    break
            self.string_count -= 1

    def get_all_strings(self) -> Iterable[str]:
        queue = deque([([], self.__data)])
        while queue:
            cur_seq, items = queue.popleft()

            if 'end_for' in items:
                for _ in range(items['end_for']):
                    yield ''.join(cur_seq)

            for item in items:
                if item == 'end_for':
                    continue

                # if in this level we have end of any strings
                queue.append((cur_seq + [item], items[item]))

    def __repr__(self):
        return f'DataTree<id={id(self)}>'

    def __str__(self):
        return self.__repr__()

    def __contains__(self, string: str) -> bool:
        # checking existing of string in tree

        if len(string) == 0:
            return False

        cur_level = self.__data

        for letter in string:
            if letter not in cur_level:
                return False
            cur_level = cur_level[letter]

        if 'end_for' in cur_level:
            return True
        return False

    def __delitem__(self, key) -> None:
        self.delete(key)

    def __len__(self):
        return self.string_count


if __name__ == '__main__':
    # tests

    from pprint import pprint
    from time import time
    from random import randrange

    max_num = 10_000_000

    # testing of searching:
    # print('search:')
    # lst = [str(i) for i in range(0, max_num)]
    #
    # tree = DataTree()
    #
    # for i in lst:
    #     tree.add(i)
    #
    # tree_time = 0
    # list_time = 0
    #
    # test_count = 1000
    #
    # for _ in range(test_count):
    #     num_to_search = str(randrange(max_num - 1000, max_num))
    #
    #     start1 = time()
    #     res1 = num_to_search in lst
    #     finish1 = time()
    #     # print(res1, finish1 - start1)
    #     list_time += (finish1 - start1)
    #
    #     start2 = time()
    #     res2 = num_to_search in tree
    #     finish2 = time()
    #     # print(res2, finish2 - start2)
    #     tree_time += (finish2 - start2)
    # print(f'tree_time: {tree_time}')
    # print(f'list_time: {list_time}')

    # testing of adding:
    print('adding:')
    max_num = 1_000_000_000_000_000_000_00
    lst = []

    tree = DataTree()

    tree_time = 0
    list_time = 0

    test_count = 10000

    for _ in range(test_count):
        num_to_add = str(randrange(max_num - 1000, max_num))

        start1 = time()
        lst.append(num_to_add)
        finish1 = time()
        # print(res1, finish1 - start1)
        list_time += (finish1 - start1)

        start2 = time()
        tree.add(num_to_add)
        finish2 = time()
        # print(res2, finish2 - start2)
        tree_time += (finish2 - start2)
    print(f'tree_time: {tree_time}')
    print(f'list_time: {list_time}')

    # testing of working:
    #
    # tree = DataTree()
    # print(tree.get_tree())
    #
    # tree.add('abc')
    # tree.add('abcdeee')
    # tree.add('abcdeee')
    # tree.add('ffff')
    # tree.add('dgbmgkbhm kgnmgjn cgfkjngfm kn gfnkofgjkpv jkpxfb dfkovbeoav,')
    # tree.add('abcdeee')
    # for i in tree.get_all_strings():
    #     print(i)

    # print(len(tree))
    # tree.add('abcdeee')
    #
    # tree.add('abcd')
    # print('abcdeee' in tree)
    # print('ab' in tree)
    #
    # print(tree.get_tree())
    # del tree['abcdeee']
    # print(tree.get_tree())
    # del tree['abcdeee']
    # print(tree.get_tree())
    # del tree['abcdeee']
    # print(tree.get_tree())
    # del tree['abcdeee']
    # print(tree.get_tree())
    # del tree['abcd']
    # print(tree.get_tree())
    # del tree['abc']
    # print(tree.get_tree())
