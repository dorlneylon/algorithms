#include "floyd.hh"

void floyd() {
    for (u32 k=0; k<n; ++k)
		for (u32 i=0; i<n; ++i)
			for (u32 j=0; j<n; ++j)
				if (d[i][k] < INF && d[k][j] < INF)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}