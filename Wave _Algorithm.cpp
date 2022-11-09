#include <iostream>
#include <vector>
#include <queue> 
#include <fstream>

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	int n, m;
	fin >> n >> m;

	std::vector<std::vector<int>> v;
	v.resize(n);
	for(int i = 0; i < n; ++i)
	{
		v[i].resize(m);
		for(int j = 0; j < m; ++j)
		{
			fin >> v[i][j];
		}
	}

	std::vector<std::vector<bool>> is_visited;
	std::vector<std::vector<int>> distance;
	is_visited.resize(n);
	distance.resize(n);
	for(int i = 0; i < n; ++i)
	{
		distance[i].resize(m, -1);
		is_visited[i].resize(m, false);
		for(int j = 0; j < m; ++j)
		{
			if(v[i][j] == 1)
			{
				is_visited[i][j] = true;
			}
		}
	}
	std::pair<int, int> source;
	std::pair<int, int> dest;
	fin >> source.first >> source.second;
	fin >> dest.first >> dest.second;

	distance[source.first][source.second] = 0;
	is_visited[source.first][source.second] = true;

	std::queue<std::pair<int, int>> q;
	q.push(source);
	while(!q.empty())
	{
		std::pair<int, int> current = q.front();
		q.pop();

		if(current == dest)
		{
			break;
		}

		const int i = current.first;
		const int j = current.second;

		if(i - 1 >= 0 && !is_visited[i - 1][j])
		{
			q.push(std::make_pair(i - 1, j));
			distance[i - 1][j] = distance[i][j] + 1;
			is_visited[i - 1][j] = true;
		}
		if(i + 1 < n && !is_visited[i + 1][j])
		{
			q.push(std::make_pair(i + 1, j));
			distance[i + 1][j] = distance[i][j] + 1;
			is_visited[i + 1][j] = true;
		}
		if(j + 1 < m && !is_visited[i][j + 1])
		{
			q.push(std::make_pair(i, j + 1));
			distance[i][j + 1] = distance[i][j] + 1;
			is_visited[i][j + 1] = true;
		}
		if(j - 1 >= 0 && !is_visited[i][j - 1])
		{
			q.push(std::make_pair(i, j - 1));
			distance[i][j - 1] = distance[i][j] + 1;
			is_visited[i][j - 1] = true;
		}
	}
	fout << distance[dest.first][dest.second] << std::endl;
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			fout << distance[i][j] << " ";
		}
		fout << std::endl;
	}
	fout << std::endl;

	system("pause");

	return 0;
}
