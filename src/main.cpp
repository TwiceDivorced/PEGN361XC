#include <iostream>
#include <iomanip>
#include <string>
#include <stack>

const float SG_BENTONITE = 2.65;
const int POUNDS_PER_SACK = 94;              // lb
const float WATER_PER_PERC_BENTONITE = 0.65; // gal

int main()
{
    // make 2 stacks, names volume and mass
    std::stack<float> volumes; // lb
    std::stack<float> masses;  // gal

    // user input for specific gravity and water-cement ratio
    float specificGravity, waterCementRatio, percentBentonite, ppgWater;

    std::cout << "Enter specific gravity of the cement: ";
    std::cin >> specificGravity;
    std::cout << "Enter water-cement ratio in gallons per sack: ";
    std::cin >> waterCementRatio;
    std::cout << "Enter percent bentonite as a percent (enter 3 for 3%): ";
    std::cin >> percentBentonite;
    std::cout << "Enter weight of water in ppg: ";
    std::cin >> ppgWater;

    // cement MV
    masses.push(POUNDS_PER_SACK);
    volumes.push(POUNDS_PER_SACK / specificGravity / ppgWater);

    // water MV
    float waterWeight = waterCementRatio * ppgWater;
    masses.push(waterWeight);
    volumes.push(waterCementRatio);

    // bentonite MV
    float bentoniteWeight = (percentBentonite / 100) * POUNDS_PER_SACK;
    float bentoniteWaterWeight = ppgWater * percentBentonite * WATER_PER_PERC_BENTONITE;
    masses.push(bentoniteWeight);
    masses.push(bentoniteWaterWeight);

    float bentoniteVolume = bentoniteWeight / SG_BENTONITE / ppgWater;
    float bentoniteWaterVolume = bentoniteWaterWeight / ppgWater;
    volumes.push(bentoniteVolume);
    volumes.push(bentoniteWaterVolume);

    // calculate total mass and volume
    float totalMass = 0;
    float totalVolume = 0;

    while (!masses.empty())
    {
        totalMass += masses.top();
        masses.pop();
    }

    while (!volumes.empty())
    {
        totalVolume += volumes.top();
        volumes.pop();
    }

    // calculate density, mix, and yield
    float density = totalMass / totalVolume;                                  // lb/gal
    float mix = (waterWeight + bentoniteWaterWeight) / POUNDS_PER_SACK * 100; // %
    float yield = totalVolume * 231 / 1728;                                   // ft^3

    std::cout << std::endl
              << std::setprecision(2) << std::fixed
              << "With the given parameters," << std::endl
              << "\tSlurry Density = " << density << " ppg" << std::endl
              << "\tPercent Mix = " << mix << " %" << std::endl
              << "\tYield = " << yield << " ft^3" << std::endl;
    return 0;
}