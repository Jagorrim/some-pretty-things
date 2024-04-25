from copy import deepcopy


class DataTree:
    # this is data structure for strings.
    # It's scalable to be structure for any collection of hashable elements
    def __init__(self) -> None:
        self.__data = {}

    def get_tree(self) -> dict:
        # returns deepcopy of tree
        return deepcopy(self.__data)

    def add(self, string: str) -> None:
        # adding new string to tree

        cur_level = self.__data
        cur_item_index = 0

        while cur_item_index < len(string):
            if string[cur_item_index] not in cur_level:
                cur_level[string[cur_item_index]] = {}

            cur_level = cur_level[string[cur_item_index]]
            cur_item_index += 1

    def delete(self, string: str) -> None:
        # deleting item from tree
        levels = [self.__data]

        cur_level = self.__data
        cur_item_index = 0

        is_string_seq_end = False

        while cur_item_index < len(string):
            if string[cur_item_index] not in cur_level:
                raise ValueError(f'Tree {self} does not contain {string}!')

            if len(cur_level[string[cur_item_index]]) == 0:
                is_string_seq_end = True
                break

            cur_level = cur_level[string[cur_item_index]]
            levels.append(cur_level)
            cur_item_index += 1

        if is_string_seq_end:
            for index in range(len(string) - 1, -1, -1):
                if len(levels[index][string[index]]) == 0:
                    del levels[index][string[index]]
                else:
                    break

    def __repr__(self):
        return f'DataTree<id={id(self)}>'

    def __str__(self):
        return self.__repr__()

    def __contains__(self, string: str) -> bool:
        # checking existing of string in tree

        if len(string) == 0:
            return False

        cur_level = self.__data
        cur_item_index = 0

        while cur_item_index < len(string):
            if string[cur_item_index] not in cur_level:
                return False

            cur_level = cur_level[string[cur_item_index]]
            cur_item_index += 1

        return True

    def __delitem__(self, key) -> None:
        self.delete(key)


if __name__ == '__main__':
    # tests

    from pprint import pprint
    from time import time
    from random import randrange

    max_num = 1_000_000_0

    lst = [str(i) for i in range(0, max_num)]

    tree = DataTree()

    for i in lst:
        tree.add(i)

    tree_time = 0
    list_time = 0

    test_count = 1000

    for _ in range(test_count):
        num_to_search = randrange(0, max_num)

        start1 = time()
        res1 = str(num_to_search) in lst
        finish1 = time()
        # print(res1, finish1 - start1)
        list_time += (finish1 - start1)

        start2 = time()
        res2 = str(num_to_search) in tree
        finish2 = time()
        # print(res2, finish2 - start2)
        tree_time += (finish2 - start2)
    print(f'tree_time: {tree_time}')
    print(f'list_time: {list_time}')

    # tree.add('pupup')
    # tree.add('puaaaa')
    # pprint(tree.get_tree())
    # tree.delete('pupup')
    # pprint(tree.get_tree())
    # tree.add('tadam')
    # pprint(tree.get_tree())
