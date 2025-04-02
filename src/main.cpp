#include <iostream>
#include <string>
#include <stack>

const int POUNDS_PER_SACK = 94;
const float PPG_WATER = 8.34;
const float SG_BENTONITE = 2.65;
const float WATER_PER_PERC_BENTONITE = 0.65; // gal

int main()
{
    // make 2 stacks, names volume and mass
    std::stack<float> volumes; // lb
    std::stack<float> masses;  // gal

    // user input for specific gravity and water-cement ratio
    float specificGravity, waterCementRatio, percentBentonite;

    std::cout << "Enter specific gravity of the cement: ";
    std::cin >> specificGravity;
    std::cout << "Enter water-cement ratio in gallons per sack: ";
    std::cin >> waterCementRatio;
    std::cout << "Enter percent bentonite as a percent (enter 3 for 3%): ";
    std::cin >> percentBentonite;

    // cement MV
    masses.push(POUNDS_PER_SACK);
    volumes.push(POUNDS_PER_SACK / specificGravity / PPG_WATER);

    // water MV
    float waterWeight = waterCementRatio * PPG_WATER;
    masses.push(waterWeight);
    volumes.push(waterCementRatio);

    // bentonite MV
    float bentoniteWeight = (percentBentonite / 100) * POUNDS_PER_SACK;
    float bentoniteWaterWeight = PPG_WATER * percentBentonite * WATER_PER_PERC_BENTONITE;
    masses.push(bentoniteWeight);
    masses.push(bentoniteWaterWeight);

    float bentoniteVolume = bentoniteWeight / SG_BENTONITE / PPG_WATER;
    float bentoniteWaterVolume = bentoniteWaterWeight / PPG_WATER;
    volumes.push(bentoniteVolume);
    volumes.push(bentoniteWaterVolume);

    std::cout
        << "Hello, World!" << std::endl;
    return 0;
}