import heapq
from functools import total_ordering


@total_ordering
class Way:
    def __init__(self, from_, to, cost):
        self.from_ = from_
        self.to = to
        self.cost = cost
        self.total_cost = cost

    def __eq__(self, other):
        return self.total_cost == other.total_cost

    def __lt__(self, other):
        return self.total_cost < other.total_cost

    def __repr__(self):
        return f'Way from:{self.from_}, to:{self.to}, cost:{self.cost}, total_cost:{self.total_cost}'


n, start, finish = map(int, input().split())
graph = {}

cur = []
done = [-1] * (n + 1)

done[start] = 0

for i in range(1, n + 1):
    nums = [int(j) for j in input().split()]
    for to in range(1, n + 1):
        if i not in graph:
            graph[i] = []

        cost = nums[to - 1]

        if cost == -1 or i == to:
            continue

        item = Way(i, to, cost)
        graph[i].append(item)

        if i == start:
            heapq.heappush(cur, item)

saw = {start}

while True:
    if not cur:
        break

    way = heapq.heappop(cur)

    if way.to in saw:
        continue

    done[way.to] = done[way.from_] + way.cost

    saw.add(way.to)

    if way.to == finish:
        break

    for new_way in graph[way.to]:
        if new_way.to in saw:
            continue

        new_way.total_cost += way.total_cost
        heapq.heappush(cur, new_way)

print(done[finish])