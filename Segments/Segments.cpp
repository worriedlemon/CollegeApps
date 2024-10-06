#include <iostream>

// How many values fit in 2 bytes
constexpr const unsigned values_in_2_bytes = (1 << 8 * sizeof(short));

// Function for taking first 20 bits
constexpr unsigned cut20bits(unsigned int F)
{
    return F % (1 << 20);
}

int main()
{
    // Random address
    constexpr int a = cut20bits(0xFFFA516);

    // Counter
    int cnt = 0;

    // Taking every segment possible
    for (int seg = 0; seg < values_in_2_bytes; seg++)
    {
        // Taking every offset possible
        for (int off = 0; off < values_in_2_bytes; off++)
        {
            // Comparing obtained address with original
            int addr = cut20bits((seg << 4) + off);
            if (addr == a) cnt++;
        }
    }

    std::cout << std::hex << "Segmentation. Address " << a << " ";
    std::cout << "can be represented in " << std::dec << cnt << " ways";

    return 0;
}