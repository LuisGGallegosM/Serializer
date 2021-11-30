
#include"JXBuild/JXBuild.h"

using namespace jxbuild;

int main(int argc,const char **argv)
{
	JXBuild build(argc, argv);
	Library Serializer("Serializer");
	build.addTarget(&Serializer);
	Serializer.install();

	Serializer.add({
		"JSON/JsonDump.cpp","JSON/JsonParser.cpp","Object.cpp","JSON/JsonDump.h",
		"JSON/JsonParser.h","CSV/CsvParser.cpp","CSV/CsvParser.h","Object.h","Serializer.h"	});


	Library Tester =Library::import("Tester");
	Executable test("tester");
	test.set(Variable::SRC_SUBDIR,"tests");
	test.add({ "test.cpp" });
	test.addDep(&Serializer);
	test.addDep(&Tester);
	build.addTest(&test, {});
	build.addTarget(&test);

	build.generate();
	return 0;
}
