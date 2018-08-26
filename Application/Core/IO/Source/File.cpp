#include "Core/IO/Headers/File.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Core
{
	namespace IO
	{
		File::File(FilePath path, OpenMode permissions, Endian endian)
			: Path(path), FilePermissions(permissions), FileEndian(endian)
		{

		}

		String File::GetFullPath()
		{
			return (Path.GetFullPath());
		}

		void File::SetPermissions(OpenMode permissions)
		{
			Close();

			FilePermissions = permissions;

			Open();
		}

		void File::Open()
		{
			cout << "Opening file <<" << GetFullPath() << ">>" << endl;

			FileStream.open(GetFullPath(), FilePermissions);

			if (!FileStream.is_open())
			{
				cout << "File could not open, attempting to create and then reopening" << endl;

				if (Create())
				{
					Open();
				}
				else
				{
					throw IOException("File <" + GetFullPath() + "> was unable to be opened");
				}
			}
		}

		void File::Close()
		{
			cout << "Closing file <<" << GetFullPath() << ">>" << endl;

			FileStream.close();
		}

		bool File::Create()
		{
			FileStream.open(GetFullPath(), ios::out);

			bool created = FileStream.is_open();

			FileStream.close();

			return created;
		}

		bool File::Delete()
		{
			return (remove(GetFullPath().c_str()) != 0);
		}

		void File::Clear()
		{
			Close();

			FileStream.open(GetFullPath(), ios::trunc); // reopen and clear
			FileStream.close();

			Open();
		}

		void File::Reset()
		{
			FileStream.clear();
		}

		bool File::AtEndOfFile()
		{
			return FileStream.eof();
		}

		bool File::CanRead()
		{
			return HasPermission(FilePermissions, ios::in);
		}

		bool File::CanWrite()
		{
			return HasPermission(FilePermissions, ios::out);
		}

		StreamPos File::GetLength()
		{
			auto currentPos = GetPosition();

			GoToPosition(0, false);
			auto finalPosition = GetPosition();

			GoToPosition(currentPos);

			return finalPosition;
		}
		
		void File::GoToPosition(StreamPos position, bool start)
		{
			auto origin = start ? ios::beg : ios::end;
			if (CanRead())
			{
				FileStream.seekg(position, origin);
			}
			else if (CanWrite())
			{
				FileStream.seekp(position, origin);
			}

			if (position != GetPosition())
			{
				throw IOException("Failed to jump to desired position");
			}
		}

		StreamPos File::GetPosition()
		{
			if (CanRead())
			{
				return FileStream.tellg();
			}
			else if (CanWrite())
			{
				return FileStream.tellp();
			}

			throw IOException("Trying to get position from <" + GetFullPath() + "> when file is closed");
		}

		bool File::MoveToNextLine()
		{
			if (CanRead())
			{
				FileStream.ignore(unsigned(-1), '\n');

				return true;
			}

			return false;
		}

		bool File::CreateNewLine()
		{
			return Write('\n');
		}

		String File::GetLine()
		{			
			if (CanRead())
			{
				String Line;
				if (!std::getline(FileStream, Line))
				{
					return "";
				}

				return Line;
			}

			throw IOException("Can't get line for this file - incorrect permissions");
		}
	}
}