#include "BPSParser.hpp"
#include <array>
#include <filesystem>
#include <iostream>
#include <nfd.hpp>

int main()
{
	NFD_Init();

	nfdchar_t* outPath = nullptr;
	std::array<nfdfilteritem_t, 1> filters = {{{"DELTARUNE Data", "win"}}};
	nfdresult_t result = NFD_OpenDialog(&outPath, filters.data(), filters.size(), nullptr);
	if (result == NFD_CANCEL)
		return 0;
	else if (result == NFD_ERROR)
	{
		std::cout << "Error: " << NFD_GetError() << std::endl;
		return 1;
	}

	try
	{
		std::string patchedFile = drfr::applyPatch(outPath, "data.bps");
		std::filesystem::rename(outPath, std::string(outPath) + ".original");
		std::filesystem::rename(patchedFile, outPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}

	NFD_Quit();
}
