#include <cstdio>
#include <cstdint>
#include <cstdlib>

// TODO: naive impl
// TODO: count on update
// TODO: spfa
// TODO: use 4bit representation

using ut = std::uint_fast32_t;
const size_t MX = 64-2;

std::uint_fast8_t grid[MX+2][MX+2];

const char output_lookup[] = { ' ', '#' };
void render_grid()
{
    for (ut i=1; i<MX; ++i) {
        for (ut j=1; j<MX; ++j)
            putchar_unlocked(output_lookup[grid[i][j]&1]);
        putchar_unlocked('\n');
    }
}

int main()
{
    puts("hello world");
    render_grid();
}

