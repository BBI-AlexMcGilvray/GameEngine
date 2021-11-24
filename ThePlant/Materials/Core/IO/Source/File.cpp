#include "Core/IO/Headers/File.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Core {
namespace IO {
  File::File(FilePath path, OpenMode permissions, Endian endian)
    : Path(path), FilePermissions(permissions), FileEndian(endian)
  {
  }

  std::string File::GetFullPath()
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
    DEBUG_LOG(TAG, "Opening file <<" + GetFullPath() + ">>");

    FileStream.open(GetFullPath(), FilePermissions);

    if (!FileStream.is_open()) {
      throw IOException("File <" + GetFullPath() + "> was unable to be opened");
    }
  }

  void File::Close()
  {
    DEBUG_LOG(TAG, "Closing file <<" + GetFullPath() + ">>");

    FileStream.close();
  }

  bool File::Create()
  {
    FileStream.open(GetFullPath(), std::ios::out);

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

    FileStream.open(GetFullPath(), std::ios::trunc);// reopen and clear
    FileStream.close();

    Open();
  }

  void File::Reset()
  {
    FileStream.clear();
  }

  bool File::AtEndOfFile() const
  {
    return FileStream.eof();
  }

  bool File::CanRead() const
  {
    return HasPermission(FilePermissions, std::ios::in);
  }

  bool File::CanWrite() const
  {
    return HasPermission(FilePermissions, std::ios::out);
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
    auto origin = start ? std::ios::beg : std::ios::end;
    if (CanRead()) {
      FileStream.seekg(position, origin);
    } else if (CanWrite()) {
      FileStream.seekp(position, origin);
    }

    if (position != GetPosition()) {
      DEBUG_THROW_EXCEPTION(IOException, TAG, "Failed to jump to desired position");
    }
  }

  StreamPos File::GetPosition()
  {
    if (CanRead()) {
      return FileStream.tellg();
    } else if (CanWrite()) {
      return FileStream.tellp();
    }

    DEBUG_THROW_EXCEPTION(IOException, TAG, "Trying to get position from <" + GetFullPath() + "> when file is closed");
  }

  bool File::MoveToNextLine()
  {
    if (CanRead()) {
      FileStream.ignore(unsigned(-1), '\n');

      return true;
    }

    return false;
  }

  bool File::CreateNewLine()
  {
    return Write('\n');
  }

  std::string File::GetFullText()
  {
    if (CanRead())
    {
      constexpr size_t buffer_size = 4096;
      auto buffer = std::string();
      buffer.reserve(buffer_size);

      while (!AtEndOfFile()) {
          buffer.append(GetLine());
          buffer.append(1, '\n');
      }

      return buffer;
    }
  }

  std::string File::GetLine()
  {
    if (CanRead()) {
      std::string Line;
      if (!std::getline(FileStream, Line)) {
        DEBUG_THROW_EXCEPTION(EOFException, TAG, "can't get line for this file - likely EOF");
      }

      return Line;
    }

    DEBUG_THROW_EXCEPTION(IOException, TAG, "Can't get line for this file - incorrect permissions");
  }
}// namespace IO
}// namespace Core