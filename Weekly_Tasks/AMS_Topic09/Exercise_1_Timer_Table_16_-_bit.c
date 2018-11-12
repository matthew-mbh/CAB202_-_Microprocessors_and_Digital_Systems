// Replace 0 with the correct value for each unknown cell.
double prescale_001 = 1;                            // 1
double prescale_010 = 8;                            // 1 * 8
double prescale_011 = 64;                           // 8 * 8
double prescale_100 = 256;                          // 64 * 4
double prescale_101 = 1024;                         // 256 * 4
double counter_freq_001 = 8000000;                  // 8000000
double counter_freq_010 = 1000000;                  // 8000000 / 8
double counter_freq_011 = 125000;                   // 1000000 / 8
double counter_freq_100 = 31250;                    // 125000 / 8
double counter_freq_101 = 7812.5;                   // 31250 / 8
double over_flow_period_001 = 0.008192;             // 65536 / 8000000
double over_flow_period_010 = 0.065536;             // 65536 / 1000000
double over_flow_period_011 = 0.524288;             // 65536 / 125000
double over_flow_period_100 = 2.097152;             // 65536 / 31250
double over_flow_period_101 = 8.388608;             // 65536 / 7812.5
double overflow_frequency_001 = 122.0703125;        // 1 / 0.008192
double overflow_frequency_010 = 15.2587890625;      // 1 / 0.065536
double overflow_frequency_011 = 1.9073486328125;    // 1 / 0.524288
double overflow_frequency_100 = 0.47683715820313;   // 1 / 2.097152
double overflow_frequency_101 = 0.11920928955078;   // 1 / 8.388608

// There is no test driver for this program.

int main() {
	for ( ;; ) {
	}

	return 0;
}

