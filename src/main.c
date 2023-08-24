#include <stdio.h>
#include <stdlib.h>
#include "IO/IO.h"
#include "PP/PP.h"

int main()
{
	sap_file file = sap_read_file("test.txt");
	sap_scs_file file2 = sap_pp_phase1(&file);
	sap_scs_file file3 = sap_pp_phase2(&file2);
	for (int i = 0; i < file3.size; ++i)
	{
		putchar(file3.data[i]);
	}
	putchar('\n');
	printf("%ld", file3.size);
}