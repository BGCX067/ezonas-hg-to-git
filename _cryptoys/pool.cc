vector<float> pool;
queue<size_t> availables;

void add(float f)
{
	if (availables.empty())
		pool.push_back(f);
	else
	{
		pool[availables.back()] = f;
		availables.pop();
	}
}

void remove(size_t index)
{
	availables.push_back(index);
}

int main()
{
for (auto it = pool.begin(); it != pool.end(); ++ it)
{
	if
}
}

/*
I have several timers which I update each frame in a game, they can appear at any moment with an arbitrary time in them. I need to modify all of them at each frame to keep accurate results.

When one counts down to zero, I need to remove it, and since it can count down to zero at any moment, I need the container to be fast.

`std::list` seems good since I can erase in middle, but it lacks performance for a large list.
`std::queue` is fast, but I can't erase in the middle. Same for `std::deque`.

I also thought about using some kind of memory pool and some std::queue of empty items


*/