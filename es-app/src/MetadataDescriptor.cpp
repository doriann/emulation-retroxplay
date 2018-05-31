//
// Created by bkg2k on 5/29/18.
//

#include "MetadataDescriptor.h"
#include "datetime/DateTime.h"
#include "Locale.h"
#include "Util.h"
#include "Log.h"

const std::string MetadataDescriptor::GameNodeIdentifier = "game";
const std::string MetadataDescriptor::FolderNodeIdentifier = "folder";

const MetadataFieldDescriptor* MetadataDescriptor::GetMetadataFieldDescriptors(int& count)
{
  // This static field descriptor array is defined here to allow
  // offsetof accessing private fields
  static const MetadataFieldDescriptor _GameMetadataDescriptors[] =
  {
    MetadataFieldDescriptor("name"       , ""        , _("Name")        , _("enter game name")             , (int)offsetof(MetadataDescriptor, _Name)       , MetadataFieldDescriptor::Type::String, false, true),
    MetadataFieldDescriptor("rating"     , "0.0"     , _("Rating")      , _("enter rating")                , (int)offsetof(MetadataDescriptor, _Rating)     , MetadataFieldDescriptor::Type::Rating, false, true),
    MetadataFieldDescriptor("favorite"   , "false"   , _("Favorite")    , _("enter favorite")              , (int)offsetof(MetadataDescriptor, _Favorite)   , MetadataFieldDescriptor::Type::Bool  , false, true),
    MetadataFieldDescriptor("hidden"     , "false"   , _("Hidden")      , _("set hidden")                  , (int)offsetof(MetadataDescriptor, _Hidden)     , MetadataFieldDescriptor::Type::Bool  , false, true),
    MetadataFieldDescriptor("emulator"   , "default" , _("Emulator")    , _("enter emulator")              , (int)offsetof(MetadataDescriptor, _Emulator)   , MetadataFieldDescriptor::Type::String, false, true),
    MetadataFieldDescriptor("core"       , "default" , _("Core")        , _("enter core")                  , (int)offsetof(MetadataDescriptor, _Core)       , MetadataFieldDescriptor::Type::String, false, true),
    MetadataFieldDescriptor("ratio"      , "auto"    , _("Ratio")       , _("enter ratio")                 , (int)offsetof(MetadataDescriptor, _Ratio)      , MetadataFieldDescriptor::Type::String, false, true),
    MetadataFieldDescriptor("desc"       , ""        , _("Description") , _("enter description")           , (int)offsetof(MetadataDescriptor, _Description), MetadataFieldDescriptor::Type::Text  , false, false),
    MetadataFieldDescriptor("image"      , ""        , _("Image")       , _("enter path to image")         , (int)offsetof(MetadataDescriptor, _Image)      , MetadataFieldDescriptor::Type::Path  , false, false),
    MetadataFieldDescriptor("thumbnail"  , ""        , _("Thumbnail")   , _("enter path to thumbnail")     , (int)offsetof(MetadataDescriptor, _Thumbnail)  , MetadataFieldDescriptor::Type::Path  , false, false),
    MetadataFieldDescriptor("releasedate", ""        , _("Release date"), _("enter release date")          , (int)offsetof(MetadataDescriptor, _ReleaseDate), MetadataFieldDescriptor::Type::Date  , false, false),
    MetadataFieldDescriptor("developer"  , "unknown" , _("Developer")   , _("enter game developer")        , (int)offsetof(MetadataDescriptor, _Developper) , MetadataFieldDescriptor::Type::String, false, false),
    MetadataFieldDescriptor("publisher"  , "unknown" , _("Publisher")   , _("enter game publisher")        , (int)offsetof(MetadataDescriptor, _Publisher)  , MetadataFieldDescriptor::Type::String, false, false),
    MetadataFieldDescriptor("genre"      , "unknown" , _("Genre")       , _("enter game genre")            , (int)offsetof(MetadataDescriptor, _Genre)      , MetadataFieldDescriptor::Type::String, false, false),
    MetadataFieldDescriptor("players"    , "1"       , _("Players")     , _("enter number of players")     , (int)offsetof(MetadataDescriptor, _Players)    , MetadataFieldDescriptor::Type::Range , false, false),
    MetadataFieldDescriptor("region"     , ""        , _("Region")      , _("enter region")                , (int)offsetof(MetadataDescriptor, _Region)     , MetadataFieldDescriptor::Type::String, false, false),
    MetadataFieldDescriptor("romtype"    , "Original", _("Romtype")     , _("enter romtype")               , (int)offsetof(MetadataDescriptor, _RomType)    , MetadataFieldDescriptor::Type::String, false, false),
    MetadataFieldDescriptor("playcount"  , "0"       , _("Play count")  , _("enter number of times played"), (int)offsetof(MetadataDescriptor, _Playcount)  , MetadataFieldDescriptor::Type::Int   , true , false),
    MetadataFieldDescriptor("lastplayed" , "0"       , _("Last played") , _("enter last played date")      , (int)offsetof(MetadataDescriptor, _LastPlayed) , MetadataFieldDescriptor::Type::Date  , true , false),
    MetadataFieldDescriptor("hash"       , "0"       , _("Rom Crc32")   , _("enter rom crc32")             , (int)offsetof(MetadataDescriptor, _RomCrc32)   , MetadataFieldDescriptor::Type::Crc32 , true , false),
  };

  count = sizeof(_GameMetadataDescriptors) / sizeof(MetadataFieldDescriptor);
  return &_GameMetadataDescriptors[0];
}

bool MetadataDescriptor::RangeToInt(const std::string& range, int& to)
{
  int p = (int)range.find('-');
  if (p == (int)std::string::npos)
  {
    if (!StringToInt(range, p)) return false;
    to = (p << 16) + p;
    return true;
  }

  int min; if (!StringToInt(range, min, 0, '-')) return false;
  int max; if (!StringToInt(range, max, p, 0  )) return false;
  to = (min << 16) + max;
  return true;
}

bool MetadataDescriptor::IntToHex(int from, std::string& to)
{
  static const char* hexa = "0123456789ABCDEF";
  char result[8];

  for(int i = sizeof(result), p = 0; -- i >= 0;)
    result[p++] = hexa[(from >> (i << 2)) & 0xF];

  to = result;
  return true;
}

bool MetadataDescriptor::HexToInt(const std::string& from, int& to)
{
  if (from.size() == 0) return false;
  const char* src = from.c_str();

  int result = 0;
  for (;; src++)
  {
    int v = src[0];
    if ((unsigned int)(v - 0x30) <= 9) { result <<= 4; result += v - 0x30; }
    else
    {
      v &= 0xDF;
      if ((unsigned int)(v - 0x41) <= 5) { result <<= 4; result += v - 0x37; }
      else break;
    }
  }
  if (src[0] != 0) return false;

  to = result;
  return true;
}

bool MetadataDescriptor::StringToInt(const std::string& from, int& to, int offset, char stop)
{
  const char* src = from.c_str() + offset;

  bool sign = (src[0] == '-');
  if (sign) src++;

  int result = 0;
  while ((unsigned int)(src[0] - 0x30) <= 9) { result *= 10; result += src[0] - 0x30; src++; }
  if (src[0] != stop) return false;

  to = sign ? -result : result;
  return true;
}

bool MetadataDescriptor::StringToInt(const std::string& from, int& to)
{
  const char* src = from.c_str();

  bool sign = (src[0] == '-');
  if (sign) src++;

  int result = 0;
  while ((unsigned int)(src[0] - 0x30) <= 9) { result *= 10; result += src[0] - 0x30; src++; }
  if (src[0] != 0) return false;

  to = sign ? -result : result;
  return true;
}

bool MetadataDescriptor::StringToFloat(const std::string& from, float& to)
{
  const char* src = from.c_str();

  bool sign = (src[0] == '-');
  if (sign) src++;

  int intPart = 0;
  int fractPart = 0;
  int pow10 = 1;

  // Integer part
  while ((unsigned int)(src[0] - 0x30) <= 9) { intPart *= 10; intPart += src[0] - 0x30; src++; }
  if (src[0] == '.')
  {
    src++;
    while ((unsigned int)(src[0] - 0x30) <= 9) { fractPart *= 10; fractPart += src[0] - 0x30; src++; pow10 *= 10; }
  }
  if (src[0] != 0) return false;

  float result = (float)intPart + ((float)fractPart / (float)pow10);

  to = sign ? -result : result;
  return true;
}

bool MetadataDescriptor::Deserialize(const Tree& from, const std::string& relativeTo)
{
  int count = 0;
  const MetadataFieldDescriptor* fields = GetMetadataFieldDescriptors(count);

  if (from.data() == GameNodeIdentifier) _Type = Type::Game;
  else if (from.data() == FolderNodeIdentifier) _Type = Type::Folder;
  else return false; // Unidentified node

  for(; --count >= 0; )
  {
    // Get field descriptor
    const MetadataFieldDescriptor& field = fields[count];

    // Get field data as string
    std::string value = from.get(field.Key(), field.DefaultValue());

    // Get neutral target
    void* target = ((unsigned char*)this) + field.Offset();

    // Convert & store
    switch(field.Iype())
    {
      case MetadataFieldDescriptor::Type::String:
      case MetadataFieldDescriptor::Type::Text:
      {
        *((std::string*)target) = value;
        break;
      }
      case MetadataFieldDescriptor::Type::Path:
      {
        value = resolvePath(value, relativeTo, true).generic_string();
        *((std::string*)target) = value;
        break;
      }
      case MetadataFieldDescriptor::Type::Int:
      {
        int intValue = 0;
        if (!StringToInt(value, intValue))
        {
          LOG(LogWarning) << "Invalid int value " << value;
          StringToInt(field.DefaultValue(), intValue);
        }
        *((int*)target) = intValue;
        break;
      }
      case MetadataFieldDescriptor::Type::Bool:
      {
        *((bool*)target) = (value == "true");
        break;
      }
      case MetadataFieldDescriptor::Type::Float:
      case MetadataFieldDescriptor::Type::Rating:
      {
        float floatValue = 0;
        if (!StringToFloat(value, floatValue))
        {
          LOG(LogWarning) << "Invalid float value " << value;
          StringToFloat(field.DefaultValue(), floatValue);
        }
        *((float*)target) = floatValue;
        break;
      }
      case MetadataFieldDescriptor::Type::Date:
      {
        *((float*)target) = DateTime(value).ToEpochTime(); // ISO 8601 constructor
        break;
      }
      case MetadataFieldDescriptor::Type::Range:
      {
        int intValue = 0;
        if (!RangeToInt(value, intValue)) { LOG(LogWarning) << "Invalid Range " << value; }
        *((int*)target) = intValue;
        break;
      }
      case MetadataFieldDescriptor::Type::Crc32:
      {
        int intValue = 0;
        if (!HexToInt(value, intValue)) { LOG(LogWarning) << "Invalid CRC32 " << value; }
        *((int*)target) = intValue;
        break;
      }
      default: throw std::logic_error("Unknown field type");
    }
  }

  return true;
}

MetadataDescriptor::Tree MetadataDescriptor::Serialize(const std::string& relativeTo)
{
  int count = 0;
  const MetadataFieldDescriptor* fields = GetMetadataFieldDescriptors(count);

  Tree result("game");

  for(; --count >= 0; )
  {
    // Get field descriptor
    const MetadataFieldDescriptor& field = fields[count];

    // Get neutral source
    void* source = ((unsigned char*)this) + field.Offset();

    // Convert & store
    switch(field.Iype())
    {
      case MetadataFieldDescriptor::Type::String:break;
      case MetadataFieldDescriptor::Type::Text:
      {
        result.add(field.Key(), *((std::string*)source));
        break;
      }
      case MetadataFieldDescriptor::Type::Path:
      {
        result.add(field.Key(), makeRelativePath(*((std::string*)source), relativeTo, true).generic_string());
        break;
      }
      case MetadataFieldDescriptor::Type::Int:
      {
        result.add(field.Key(), *((int*)source)); // Autoboxing std::string(int)
        break;
      }
      case MetadataFieldDescriptor::Type::Bool:
      {
        result.add(field.Key(), *((bool*)source) ? "true" : "false");
        break;
      }
      case MetadataFieldDescriptor::Type::Float:break;
      case MetadataFieldDescriptor::Type::Rating:
      {
        result.add(field.Key(), *((float*)source)); // Autoboxing std::string(float)
        break;
      }
      case MetadataFieldDescriptor::Type::Date:
      {
        result.add(field.Key(), DateTime((long long)*((int*)source)).ToISO8601());
        break;
      }
      case MetadataFieldDescriptor::Type::Range:
      {
        int intValue = *((int*)source);
        std::string value;
        value += (intValue >> 16);
        value += '-';
        value += (intValue & 0xFFFF);
        result.add(field.Key(), value);
        break;
      }
      case MetadataFieldDescriptor::Type::Crc32:
      {
        std::string value;
        IntToHex(*((int*)source), value);
        result.add(field.Key(), value);
        break;
      }
      default: throw std::logic_error("Unknown field type");
    }
  }

  return std::move(result);
}
