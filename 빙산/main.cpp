#include <iostream>
#include <queue>

using namespace std;

int nfiled[301][301];
int ncopy[301][301];
int x, y;

int dirx[] = { 0, 0, 1, -1 };
int diry[] = { 1, -1, 0, 0 };

typedef struct pos
{
	int nx, ny;
};

int nRet;

int bfs()
{
	queue <pos> que;
	pos cur = { 0, 0 };
	pos nxt = { 0, 0 };
	int iceburg = 0;

	int nvisit[301][301] = { 0, };

	for (int i = 0; i < y; i++){
		for (int j = 0; j < x; j++){
			if (nfiled[i][j] && !nvisit[i][j]){
				iceburg++;
				nvisit[i][j] = 1;
				que.push({ j, i });
				while (!que.empty())
				{
					cur = que.front();
					que.pop();

					for (int d = 0; d < 4; d++){
						nxt.nx = cur.nx + dirx[d];
						nxt.ny = cur.ny + diry[d];

						if (nxt.nx < 0 || nxt.nx >= x || nxt.ny  < 0 || nxt.ny >= y) continue;

						if (nfiled[nxt.ny][nxt.nx] && !nvisit[nxt.ny][nxt.nx]){
							que.push(nxt);
							nvisit[nxt.ny][nxt.nx] = 1;
						}

					}
				}

			}
		}
	}
	return iceburg;
}



int main()
{
	cin >> y >> x;

	for (int i = 0; i < y; i++){
		for (int j = 0; j < x; j++){
			cin >> nfiled[i][j];
			ncopy[i][j] = nfiled[i][j];
		}
	}

	bool flag = true;
	int nextx = 0;
	int nexty = 0;
	int iceburg = 0;

	while (flag)
	{
		for (int i = 0; i < y; i++){
			for (int j = 0; j < x; j++){
				if (nfiled[i][j]){
					for (int d = 0; d < 4; d++){
						nextx = j + dirx[d];
						nexty = i + diry[d];

						if (nextx < 0 || nextx >= x || nexty < 0 || nexty >= y) continue;

						if (!nfiled[nexty][nextx]){
							ncopy[i][j] = ncopy[i][j] - 1;
							if (ncopy[i][j] == -1)
								ncopy[i][j] = 0;
						}
					}
				}
			}
		}

		for (int i = 0; i < y; i++){
			for (int j = 0; j < x; j++){
				nfiled[i][j] = ncopy[i][j];
			}
		}

		nRet = bfs();

		if (nRet >= 2)
			flag = false;
		else if (nRet == 0) // 빙산이 하나도 없을 경우 처리 해줘야함.
		{
			cout << 0 << endl;
			return 0;
		}
		iceburg++;
	}

	cout << iceburg << endl;
	return 0;
}