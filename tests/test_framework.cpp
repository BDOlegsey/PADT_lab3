#include "test_framework.h"

namespace lab3 {
namespace tests {

int t_passed = 0;
int t_failed = 0;
int t_total  = 0;

void ResetCounters() { t_passed = t_failed = t_total = 0; }

void PrintSummary() {
    int coverage = (t_total > 0) ? (100 * t_passed) / t_total : 0;
    std::printf("All:      %d\n", t_total);
    std::printf("Done:     %d\n", t_passed);
    std::printf("Fall:     %d\n", t_failed);
    std::printf("Coverage: %d%%\n", coverage);
}

}  // namespace tests
}  // namespace lab3
