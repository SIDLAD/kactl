/**
 * Author: Siddharth
 * Date: 2024-12-22
 * Description: Mobius function 
 */

#pragma once

vector<int> mobius(VALMAX)
mobius[1] = -1;
for (int i = 1; i < VALMAX; i++) {
	if (mobius[i]) {
		mobius[i] = -mobius[i];
		for (int j = 2 * i; j < VALMAX; j += i) { mobius[j] += mobius[i]; }
	}
}
