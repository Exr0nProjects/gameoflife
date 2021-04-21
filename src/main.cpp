#include <cstdio>
#include <cstdint>
#include <cstdlib>

// TODO: use 4bit representation

using nt = std::int_fast32_t;
const size_t MX = 4;

std::uint_fast8_t grid[MX+2][MX+2];

const char output_lookup[] = { '.', '#' };
void render_grid()
{
    for (nt i=1; i<=MX; ++i) {
        for (nt j=1; j<=MX; ++j)
            putchar_unlocked(' '),
            //putchar_unlocked(grid[i][j]/2 + '0'),
            printf("%d", grid[i][j]/2),
            putchar_unlocked(output_lookup[grid[i][j]&1]);
        putchar_unlocked('\n');
    }
    putchar_unlocked('\n');
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
    grid[y][x] &= ~1;                    // set cell as dead
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

nt birth_sz=0, birth_y[MX*MX], birth_x[MX*MX],
   death_sz=0, death_y[MX*MX], death_x[MX*MX];
void calc_gen()
{
    // find next generation
    for (nt i=1; i<=MX; ++i) {
        for (nt j=1; j<=MX; ++j) {
            if (grid[i][j]&1) {         // currently alive
                //printf("%lu %lu alive %d\n", i, j, grid[i][j]>>1);
                if (grid[i][j]>>1 != 2 && grid[i][j]>>1 != 3)
                    ++death_sz, death_y[death_sz] = i, death_x[death_sz] = j;
            } else {                    // currently dead
                //printf("%lu %lu dead  %d\n", i, j, grid[i][j]>>1);
                if (grid[i][j]>>1 == 3) // should become alive
                    ++birth_sz, birth_y[birth_sz] = i, birth_x[birth_sz] = j;
            }
        }
    }
}

void step_gen()
{
    // step next generation
    while (birth_sz) set_alive(birth_y[birth_sz], birth_x[birth_sz]), --birth_sz;
    while (death_sz) set_dead (death_y[death_sz], death_x[death_sz]), --death_sz;
}

int main()
{
    puts("hello world");
    init_grid();
    render_grid();
    while (true) {
        calc_gen();
        if (!birth_sz && !death_sz) {
            printf("Equilibrium Reached\n");
            return 0;
        }
        step_gen();
        render_grid();
        getchar_unlocked();
    }
}

