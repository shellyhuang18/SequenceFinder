using namespace std;
#include <iostream>
#include "SequenceMap.h"
#include <vector>
#include <string>

int main(){
	SequenceMap a("dfsdfsdsf", "fewfefw");
	SequenceMap b("fffffff", "ioweiowuiot");

	a.Merge(b);

	cout << a;
}
