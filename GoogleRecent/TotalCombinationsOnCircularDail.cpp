#include <vector>
#include <bit>       // std::popcount (C++20), or use __builtin_popcount
using namespace std;

// Bitmask of all digits reachable from `center` within `maxSteps`
// clicks on a circular dial with `numDigits` positions (0..numDigits-1).
int ReachableDigitsMask(int center, int maxSteps, int numDigits) {
    if (maxSteps == 0) {
        return 1 << center;
    }
    // If the window (2*maxSteps + 1) covers the whole dial, everything is reachable.
    if (2 * maxSteps + 1 >= numDigits) {
        return (1 << numDigits) - 1;
    }

    int start = (center - maxSteps + numDigits) % numDigits;
    int end   = (center + maxSteps) % numDigits;

    int mask = 0;
    for (int d = start; ; d = (d + 1) % numDigits) {
        mask |= (1 << d);
        if (d == end) break;
    }
    return mask;
}

// Number of codes within `maxSteps` clicks (per digit) of code1 OR code2,
// on a dial with `numDigits` positions, via inclusion-exclusion.
long long CountNearbyCodes(int numDigits, int maxSteps,
                            const vector<int>& code1, const vector<int>& code2) {
    long long onlyCode1Reach = 1;   // codes near code1
    long long onlyCode2Reach = 1;   // codes near code2
    long long bothReach      = 1;   // codes near BOTH (the overlap)

    for (size_t i = 0; i < code1.size(); ++i) {
        int mask1 = ReachableDigitsMask(code1[i], maxSteps, numDigits);
        int mask2 = ReachableDigitsMask(code2[i], maxSteps, numDigits);
        int overlapMask = mask1 & mask2;

        onlyCode1Reach *= __builtin_popcount(mask1);
        onlyCode2Reach *= __builtin_popcount(mask2);
        bothReach      *= __builtin_popcount(overlapMask);
    }

    // |A ∪ B| = |A| + |B| - |A ∩ B|
    return onlyCode1Reach + onlyCode2Reach - bothReach;
}