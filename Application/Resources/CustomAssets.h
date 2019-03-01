#pragma once

#include "Data/Headers/AssetType.h"

/*
This file is auto-generated.

DO NOT MODIFY
*/

namespace Data
{

// Test
	struct Test
	{
		String Name;
	};

	template<>
	struct AssetType<Test>
	{
		Hash ClassHash() const
		{
			return Core::HashValue("Test");
		}

		String GetPath() const
		{
			return "CustomAssets/Test/";
		}

		String GetFileType() const
		{
			return ".Tst";
		}
	};

// ListTest
	struct ListTest
	{
		String Name;
		AssetName<int> TestList;
	};

	template<>
	struct AssetType<ListTest>
	{
		Hash ClassHash() const
		{
			return Core::HashValue("ListTest");
		}

		String GetPath() const
		{
			return "CustomAssets/ListTest/";
		}

		String GetFileType() const
		{
			return ".Lst";
		}
	};

// Test2
	struct Test2
	{
		String Name;
		AssetName<int> TestReference;
	};

	template<>
	struct AssetType<Test2>
	{
		Hash ClassHash() const
		{
			return Core::HashValue("Test2");
		}

		String GetPath() const
		{
			return "CustomAssets/Test2/";
		}

		String GetFileType() const
		{
			return ".Tst";
		}
	};

}
