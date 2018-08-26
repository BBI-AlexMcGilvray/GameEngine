#pragma once

#include "IODefs.h"

namespace Core
{
	namespace IO
	{
		struct File
		{
			FilePath Path;

			OpenMode FilePermissions;
			Endian FileEndian;
			/*
				should also have a BIT cursor position, with the current CursorPosition referring to the byte position, so that we can read out the exact number of
				bits for whatever data type is required by using sizeof() to get bit count, and handling the EXACT positioning ourselves.
			*/

			IOFStreamChar FileStream;

			File(FilePath path, OpenMode permissions, Endian endian = Endian::Big);

			String GetFullPath();

			void SetPermissions(OpenMode permissions);

			void Open();
			void Close();

			bool Create();
			bool Delete();
			void Clear();

			void Reset();

			bool AtEndOfFile();

			bool CanRead();
			bool CanWrite();

			StreamPos GetLength();

			void GoToPosition(StreamPos position, bool start = true);
			StreamPos GetPosition();

			bool MoveToNextLine();
			bool CreateNewLine();

			String GetLine();

			template <typename T>
			bool Read(T&& target)
			{
				if (CanRead())
				{
					if (AtEndOfFile())
					{
						return false;
					}

					return ReadToTarget(target);
				}

				throw IOException("Can't read from this file - incorrect permissions");
			}

			template <typename T, typename ...Ts>
			bool Read(T&& target, Ts&& ...args)
			{
				if (Read(target))
				{
					return Read(forward<Ts>(args)...);
				}

				return false;
			}

			template <typename T>
			bool Write(T&& source)
			{
				if (CanWrite())
				{
					return WriteFromSource(source);
				}

				throw IOException("Can't write to this file - incorrect permissions");
			}

			template <typename T, typename ...Ts>
			bool Write(T&& source, Ts&& ...args)
			{
				if (Write(source))
				{
					return Write(forward<Ts>(args)...);
				}
				return false;
			}

		private:
			template <typename T>
			bool ReadToTarget(T&& target)
			{
				if (FileStream >> target)
				{
					return true;
				}

				throw IOException("Failed to read from source to target");
				return false;
			}

			template <typename T>
			bool WriteFromSource(T&& source)
			{
				if(FileStream << source)
				{
					return true;
				}

				throw IOException("Failed to write to target from source");
				return false;
			}
		};
	}
}