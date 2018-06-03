//
// Created by bkg2k on 5/29/18.
//

#include "MetadataDescriptor.h"
#include "MetadataFieldDescriptor.h"
#include "Locale.h"
#include "Util.h"
#include "Log.h"

const std::string MetadataDescriptor::GameNodeIdentifier = "game";
const std::string MetadataDescriptor::FolderNodeIdentifier = "folder";

const MetadataFieldDescriptor* MetadataDescriptor::GetMetadataFieldDescriptors(MetadataDescriptor::ObjectType type, int& count)
{
  switch(type)
  {
    case ObjectType::Game:
    {
      // This static field descriptor array is defined here to allow
      // offsetof accessing private fields
      static const MetadataFieldDescriptor _GameMetadataDescriptors[] =
      {
        MetadataFieldDescriptor("name"       , ""        , _("Name")        , _("enter game name")             , (int)offsetof(MetadataDescriptor, _Name)       , MetadataFieldDescriptor::DataType::String, &MetadataDescriptor::IsDefaultName           , &MetadataDescriptor::NameAsString        , &MetadataDescriptor::SetName                , false, true),
        MetadataFieldDescriptor("rating"     , "0.0"     , _("Rating")      , _("enter rating")                , (int)offsetof(MetadataDescriptor, _Rating)     , MetadataFieldDescriptor::DataType::Rating, &MetadataDescriptor::IsDefaultRating         , &MetadataDescriptor::RatingAsString      , &MetadataDescriptor::SetRatingAsString      , false, true),
        MetadataFieldDescriptor("favorite"   , "false"   , _("Favorite")    , _("enter favorite")              , (int)offsetof(MetadataDescriptor, _Favorite)   , MetadataFieldDescriptor::DataType::Bool  , &MetadataDescriptor::IsDefaultFavorite       , &MetadataDescriptor::FavoriteAsString    , &MetadataDescriptor::SetFavoriteAsString    , false, true),
        MetadataFieldDescriptor("hidden"     , "false"   , _("Hidden")      , _("set hidden")                  , (int)offsetof(MetadataDescriptor, _Hidden)     , MetadataFieldDescriptor::DataType::Bool  , &MetadataDescriptor::IsDefaultHidden         , &MetadataDescriptor::HiddenAsString      , &MetadataDescriptor::SetHiddenAsString      , false, true),
        MetadataFieldDescriptor("emulator"   , "default" , _("Emulator")    , _("enter emulator")              , (int)offsetof(MetadataDescriptor, _Emulator)   , MetadataFieldDescriptor::DataType::List  , &MetadataDescriptor::IsDefaultEmulator       , &MetadataDescriptor::EmulatorAsString    , &MetadataDescriptor::SetEmulator            , false, true),
        MetadataFieldDescriptor("core"       , "default" , _("Core")        , _("enter core")                  , (int)offsetof(MetadataDescriptor, _Core)       , MetadataFieldDescriptor::DataType::List  , &MetadataDescriptor::IsDefaultCore           , &MetadataDescriptor::CoreAsString        , &MetadataDescriptor::SetCore                , false, true),
        MetadataFieldDescriptor("ratio"      , "auto"    , _("Ratio")       , _("enter ratio")                 , (int)offsetof(MetadataDescriptor, _Ratio)      , MetadataFieldDescriptor::DataType::List  , &MetadataDescriptor::IsDefaultRatio          , &MetadataDescriptor::RatioAsString       , &MetadataDescriptor::SetRatio               , false, true),
        MetadataFieldDescriptor("desc"       , ""        , _("Description") , _("enter description")           , (int)offsetof(MetadataDescriptor, _Description), MetadataFieldDescriptor::DataType::Text  , &MetadataDescriptor::IsDefaultDescription    , &MetadataDescriptor::DescriptionAsString , &MetadataDescriptor::SetDescription         , false, false),
        MetadataFieldDescriptor("image"      , ""        , _("Image")       , _("enter path to image")         , (int)offsetof(MetadataDescriptor, _Image)      , MetadataFieldDescriptor::DataType::Path  , &MetadataDescriptor::IsDefaultImage          , &MetadataDescriptor::ImageAsString       , &MetadataDescriptor::SetImagePath           , false, false),
        MetadataFieldDescriptor("thumbnail"  , ""        , _("Thumbnail")   , _("enter path to thumbnail")     , (int)offsetof(MetadataDescriptor, _Thumbnail)  , MetadataFieldDescriptor::DataType::Path  , &MetadataDescriptor::IsDefaultThumbnail      , &MetadataDescriptor::ThumbnailAsString   , &MetadataDescriptor::SetThumbnailPath       , false, false),
        MetadataFieldDescriptor("releasedate", ""        , _("Release date"), _("enter release date")          , (int)offsetof(MetadataDescriptor, _ReleaseDate), MetadataFieldDescriptor::DataType::Date  , &MetadataDescriptor::IsDefaultReleaseDateEpoc, &MetadataDescriptor::ReleaseDateAsString , &MetadataDescriptor::SetReleaseDateAsString , false, false),
        MetadataFieldDescriptor("developer"  , "unknown" , _("Developer")   , _("enter game developer")        , (int)offsetof(MetadataDescriptor, _Developer)  , MetadataFieldDescriptor::DataType::String, &MetadataDescriptor::IsDefaultDeveloper      , &MetadataDescriptor::DeveloperAsString   , &MetadataDescriptor::SetDeveloper           , false, false),
        MetadataFieldDescriptor("publisher"  , "unknown" , _("Publisher")   , _("enter game publisher")        , (int)offsetof(MetadataDescriptor, _Publisher)  , MetadataFieldDescriptor::DataType::String, &MetadataDescriptor::IsDefaultPublisher      , &MetadataDescriptor::PublisherAsString   , &MetadataDescriptor::SetPublisher           , false, false),
        MetadataFieldDescriptor("genre"      , "unknown" , _("Genre")       , _("enter game genre")            , (int)offsetof(MetadataDescriptor, _Genre)      , MetadataFieldDescriptor::DataType::String, &MetadataDescriptor::IsDefaultGenre          , &MetadataDescriptor::GenreAsString       , &MetadataDescriptor::SetGenre               , false, false),
        MetadataFieldDescriptor("players"    , "1"       , _("Players")     , _("enter number of players")     , (int)offsetof(MetadataDescriptor, _Players)    , MetadataFieldDescriptor::DataType::Range , &MetadataDescriptor::IsDefaultPlayerRange    , &MetadataDescriptor::PlayersAsString     , &MetadataDescriptor::SetPlayersAsString     , false, false),
        MetadataFieldDescriptor("region"     , ""        , _("Region")      , _("enter region")                , (int)offsetof(MetadataDescriptor, _Region)     , MetadataFieldDescriptor::DataType::String, &MetadataDescriptor::IsDefaultRegion         , &MetadataDescriptor::RegionAsString      , &MetadataDescriptor::SetRegion              , false, false),
        MetadataFieldDescriptor("romtype"    , "Original", _("Romtype")     , _("enter romtype")               , (int)offsetof(MetadataDescriptor, _RomType)    , MetadataFieldDescriptor::DataType::String, &MetadataDescriptor::IsDefaultRomType        , &MetadataDescriptor::RomTypeAsString     , &MetadataDescriptor::SetRomType             , false, false),
        MetadataFieldDescriptor("playcount"  , "0"       , _("Play count")  , _("enter number of times played"), (int)offsetof(MetadataDescriptor, _Playcount)  , MetadataFieldDescriptor::DataType::Int   , &MetadataDescriptor::IsDefaultPlayCount      , &MetadataDescriptor::PlayCountAsString   , &MetadataDescriptor::SetPlayCountAsString   , true , false),
        MetadataFieldDescriptor("lastplayed" , ""        , _("Last played") , _("enter last played date")      , (int)offsetof(MetadataDescriptor, _LastPlayed) , MetadataFieldDescriptor::DataType::Date  , &MetadataDescriptor::IsDefaultLastPlayedEpoc , &MetadataDescriptor::LastPlayedAsString  , &MetadataDescriptor::SetLastPlayedAsString  , true , false),
        MetadataFieldDescriptor("hash"       , "0"       , _("Rom Crc32")   , _("enter rom crc32")             , (int)offsetof(MetadataDescriptor, _RomCrc32)   , MetadataFieldDescriptor::DataType::Crc32 , &MetadataDescriptor::IsDefaultRomCrc32       , &MetadataDescriptor::RomCrc32AsString    , &MetadataDescriptor::SetRomCrc32AsString    , true , false),
      };

      count = sizeof(_GameMetadataDescriptors) / sizeof(MetadataFieldDescriptor);
      return &_GameMetadataDescriptors[0];
    }
    case ObjectType::Folder:
    {
      // This static field descriptor array is defined here to allow
      // offsetof accessing private fields
      static const MetadataFieldDescriptor _FolderMetadataDescriptors[] =
      {
        MetadataFieldDescriptor("name"       , ""        , _("Name")        , _("enter game name")             , (int)offsetof(MetadataDescriptor, _Name)       , MetadataFieldDescriptor::DataType::String, &MetadataDescriptor::IsDefaultName           , &MetadataDescriptor::NameAsString        , &MetadataDescriptor::SetName                , false, true),
        MetadataFieldDescriptor("hidden"     , "false"   , _("Hidden")      , _("set hidden")                  , (int)offsetof(MetadataDescriptor, _Hidden)     , MetadataFieldDescriptor::DataType::Bool  , &MetadataDescriptor::IsDefaultHidden         , &MetadataDescriptor::HiddenAsString      , &MetadataDescriptor::SetHiddenAsString      , false, true),
        MetadataFieldDescriptor("desc"       , ""        , _("Description") , _("enter description")           , (int)offsetof(MetadataDescriptor, _Description), MetadataFieldDescriptor::DataType::Text  , &MetadataDescriptor::IsDefaultDescription    , &MetadataDescriptor::DescriptionAsString , &MetadataDescriptor::SetDescription         , false, false),
        MetadataFieldDescriptor("image"      , ""        , _("Image")       , _("enter path to image")         , (int)offsetof(MetadataDescriptor, _Image)      , MetadataFieldDescriptor::DataType::Path  , &MetadataDescriptor::IsDefaultImage          , &MetadataDescriptor::ImageAsString       , &MetadataDescriptor::SetImagePath           , false, false),
        MetadataFieldDescriptor("thumbnail"  , ""        , _("Thumbnail")   , _("enter path to thumbnail")     , (int)offsetof(MetadataDescriptor, _Thumbnail)  , MetadataFieldDescriptor::DataType::Path  , &MetadataDescriptor::IsDefaultThumbnail      , &MetadataDescriptor::ThumbnailAsString   , &MetadataDescriptor::SetThumbnailPath       , false, false),
      };

      count = sizeof(_FolderMetadataDescriptors) / sizeof(MetadataFieldDescriptor);
      return &_FolderMetadataDescriptors[0];
    }
    default: break;
  }
  count = 0;
  return nullptr;
}

MetadataDescriptor MetadataDescriptor::_Default = MetadataDescriptor::BuildDefaultValueMetadataDescriptor();

MetadataDescriptor MetadataDescriptor::BuildDefaultValueMetadataDescriptor()
{
  MetadataDescriptor defaultData("default");
  TreeNode emptyGameNode;
  emptyGameNode.first = GameNodeIdentifier;
  defaultData.Deserialize(emptyGameNode, "");
  return std::move(defaultData);
}

std::string MetadataDescriptor::FloatToString(float value, int precision)
{
  int ipart = (int)value;
  value -= (float)ipart;

  // convert integer part to string
  std::string result = std::to_string(ipart);

  // check for display option after point
  if (precision > 0)
  {
    result += '.';
    value *= (float)pow(10, precision);
    result += std::to_string((int)value); // TODO: Get XAString::ToInt and get rid of that @#%$*!!! to_string
  }
  return result;
}

std::string MetadataDescriptor::IntToRange(int range)
{
  std::string value = std::to_string(range >> 16);
  value += '-';
  value += std::to_string(range & 0xFFFF);
  return std::move(value);
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
  if (min > max) { min = min ^ max; max = max ^ min; min = min ^ max; }
  to = (max << 16) + min;
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

bool MetadataDescriptor::Deserialize(const TreeNode& from, const std::string& relativeTo)
{
  if (from.first == GameNodeIdentifier) _Type = ObjectType::Game;
  else if (from.first == FolderNodeIdentifier) _Type = ObjectType::Folder;
  else return false; // Unidentified node

  int count = 0;
  const MetadataFieldDescriptor* fields = GetMetadataFieldDescriptors(_Type, count);

  // Extract default name
  std::string defaultName = std::move(_Name);

  for(; --count >= 0; )
  {
    // Get field descriptor
    const MetadataFieldDescriptor& field = fields[count];

    // Get field data as string
    const std::string& defaultStringValue = field.DefaultValue();
    std::string value = from.second.get(field.Key(), defaultStringValue);
    // Ignore default values
    if (value == defaultStringValue) continue;

    // Get neutral target
    void* target = ((unsigned char*)this) + field.Offset();

    // Convert & store
    // We could use field.SetValueMethod() to set fields by string values,
    // but we want to do more control that simple assignations
    switch(field.Type())
    {
      case MetadataFieldDescriptor::DataType::String:
      case MetadataFieldDescriptor::DataType::Text:
      case MetadataFieldDescriptor::DataType::List:
      {
        *((std::string*)target) = value;
        break;
      }
      case MetadataFieldDescriptor::DataType::Path:
      {
        value = resolvePath(value, relativeTo, true).generic_string();
        *((std::string*)target) = value;
        break;
      }
      case MetadataFieldDescriptor::DataType::Int:
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
      case MetadataFieldDescriptor::DataType::Bool:
      {
        *((bool*)target) = (value == "true");
        break;
      }
      case MetadataFieldDescriptor::DataType::Float:
      case MetadataFieldDescriptor::DataType::Rating:
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
      case MetadataFieldDescriptor::DataType::Date:
      {
        DateTime dt(false); // Unitialized DateTime
        if (dt.ParseFromString("%yyyy%MM%ddT%hh%mm%ss", value, dt))
          *((int*)target) = (int)dt.ToEpochTime();
        else
          LOG(LogWarning) << "Invalid DateTime value " << value;
        break;
      }
      case MetadataFieldDescriptor::DataType::Range:
      {
        int intValue = 0;
        if (!RangeToInt(value, intValue)) { LOG(LogWarning) << "Invalid Range " << value; }
        *((int*)target) = intValue;
        break;
      }
      case MetadataFieldDescriptor::DataType::Crc32:
      {
        int intValue = 0;
        if (!HexToInt(value, intValue)) { LOG(LogWarning) << "Invalid CRC32 " << value; }
        *((int*)target) = intValue;
        break;
      }
      default: throw std::logic_error("Unknown field type");
    }
  }

  // Control name
  if (_Name.empty())
  {
    _Name = std::move(defaultName);
    _Dirty = true;
  }

  return true;
}

MetadataDescriptor::TreeNode MetadataDescriptor::Serialize(const std::string& relativeTo) const
{
  int count = 0;
  const MetadataFieldDescriptor* fields = GetMetadataFieldDescriptors(_Type, count);

  TreeNode result;
  result.first = _Type == ObjectType::Game ? GameNodeIdentifier : FolderNodeIdentifier;
  Tree& tree = result.second;

  for(; --count >= 0; )
  {
    // Get field descriptor
    const MetadataFieldDescriptor& field = fields[count];

    // Default value?
    IsDefaultValueMethodType method = field.IsDefaultValueMethod();
    if ((this->*method)()) continue;

    // Get neutral source
    void* source = ((unsigned char*)this) + field.Offset();

    // Convert & store
    // As for Deserialize, we do not use field.GetValues, because we need
    // to do additional tasks regarding the type
    switch(field.Type())
    {
      case MetadataFieldDescriptor::DataType::String:break;
      case MetadataFieldDescriptor::DataType::Text:
      case MetadataFieldDescriptor::DataType::List:
      {
        tree.add(field.Key(), *((std::string*)source));
        break;
      }
      case MetadataFieldDescriptor::DataType::Path:
      {
        tree.add(field.Key(), makeRelativePath(*((std::string*)source), relativeTo, true).generic_string());
        break;
      }
      case MetadataFieldDescriptor::DataType::Int:
      {
        tree.add(field.Key(), *((int*)source)); // Autoboxing std::string(int)
        break;
      }
      case MetadataFieldDescriptor::DataType::Bool:
      {
        tree.add(field.Key(), *((bool*)source) ? "true" : "false");
        break;
      }
      case MetadataFieldDescriptor::DataType::Float:break;
      case MetadataFieldDescriptor::DataType::Rating:
      {
        tree.add(field.Key(), *((float*)source)); // Autoboxing std::string(float)
        break;
      }
      case MetadataFieldDescriptor::DataType::Date:
      {
        tree.add(field.Key(), DateTime((long long)*((int*)source)).ToUtc().ToISO8601());
        break;
      }
      case MetadataFieldDescriptor::DataType::Range:
      {
        tree.add(field.Key(), IntToRange(*((int*)source)));
        break;
      }
      case MetadataFieldDescriptor::DataType::Crc32:
      {
        std::string value;
        IntToHex(*((int*)source), value);
        tree.add(field.Key(), value);
        break;
      }
      default: throw std::logic_error("Unknown field type");
    }
  }

  return std::move(result);
}

void MetadataDescriptor::Merge(const MetadataDescriptor& sourceMetadata)
{
  int count = 0;
  const MetadataFieldDescriptor* fields = GetMetadataFieldDescriptors(_Type, count);

  for(; --count >= 0; )
  {
    // Get field descriptor
    const MetadataFieldDescriptor& field = fields[count];

    // Default value?
    IsDefaultValueMethodType method = field.IsDefaultValueMethod();
    if ((this->*method)()) continue;

    // Get neutral source
    void* source = ((unsigned char*)&sourceMetadata) + field.Offset();
    void* destination = ((unsigned char*)this) + field.Offset();

    // Convert & store
    switch(field.Type())
    {
      case MetadataFieldDescriptor::DataType::String:break;
      case MetadataFieldDescriptor::DataType::Text:
      case MetadataFieldDescriptor::DataType::List:
      case MetadataFieldDescriptor::DataType::Path:
      {
        *((std::string*)destination) = *((std::string*)source);
        break;
      }
      case MetadataFieldDescriptor::DataType::Date:
      case MetadataFieldDescriptor::DataType::Range:
      case MetadataFieldDescriptor::DataType::Crc32:
      case MetadataFieldDescriptor::DataType::Int:
      {
        *((int*)destination) = *((int*)source);
        break;
      }
      case MetadataFieldDescriptor::DataType::Bool:
      {
        *((bool*)destination) = *((bool*)source);
        break;
      }
      case MetadataFieldDescriptor::DataType::Float:break;
      case MetadataFieldDescriptor::DataType::Rating:
      {
        *((float*)destination) = *((float*)source);
        break;
      }
      default: throw std::logic_error("Unknown field type");
    }

    // A field has been copied. Set the dirty flag
    _Dirty = true;
  }
}
