#include <cstdio>
#include <cstdint>
#include <cstdlib>

// TODO: naive impl
// TODO: count on update
// TODO: spfa
// TODO: use 4bit representation

using nt = std::int_fast32_t;
const size_t MX = 16-2;

std::uint_fast8_t grid[MX+2][MX+2];

const char output_lookup[] = { ' ', '#' };
void render_grid()
{
    for (nt i=1; i<=MX; ++i) {
        for (nt j=1; j<=MX; ++j)
            putchar_unlocked(' '),
            putchar_unlocked(grid[i][j]/2 + '0'),
            putchar_unlocked(output_lookup[grid[i][j]&1]);
        putchar_unlocked('\n');
    }
}

void set_alive(nt y, nt x)
{
    // OPTM: this code is probably quite hot
    grid[y][x] |= 1;                    // set cell as alive
    for (nt dx=-1; dx<2; ++dx)
        for (nt dy=-1; dy<2; ++dy)
            grid[y+dy][x+dx] += 2;      // add one to each surrounding cell
    grid[y][x] -= 2;                    // don't add one to self
}

void set_dead(nt y, nt x)
{
    // OPTM: this code is probably quite hot
    grid[y][x] &= 0;                    // set cell as dead
    for (nt dx=-1; dx<2; ++dx)
        for (nt dy=-1; dy<2; ++dy)
            grid[y+dy][x+dx] -= 2;      // subtract one from each surrounding cell
    grid[y][x] += 2;                    // don't subtract one from self
}

void init_grid()
{
    std::srand(0x326ccc); // :sunglasses:
    for (nt i=1; i<=MX; ++i) {
        for (nt j=1; j<=MX; ++j) {
            nt g = rand();
            if (g&1) set_alive(i, j);
        }
    }
}

int main()
{
    puts("hello world");
    init_grid();
    render_grid();
}

