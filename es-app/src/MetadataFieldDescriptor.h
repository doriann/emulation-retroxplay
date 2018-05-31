#pragma once

#include <string>
#include <stdexcept>

class MetadataFieldDescriptor
{
  public:
    //! Data type
    enum class Type
    {
        String, //!< std::string
        Int,    //!< int
        Bool,   //!< bool
        Float,  //!< float

        Text,   //!< Multiline test (string)
        Path,   //!< File path (string)
        Rating, //!< Floating point value between 0.0 and 1.0 (float)
        Date,   //!< Epoc (int)
        Range,  //!< Integer range: LSW:from MSW:to
        Crc32,  //!< 4byte hash (int)
    };

  private:
    std::string  _Key;           //!< Identifier
    std::string  _DefaultValue;  //!< default value
    std::string  _DisplayName;   //!< displayed as this in editors
    std::string  _DisplayPrompt; //!< phrase displayed in editors when prompted to enter value (currently only for strings)
    int          _Offset;        //!< Offset of the real field in the target Metadata structure
    Type         _Iype;          //!< Datatype
    bool         _IsStatistic;   //!< if true, ignore scraper values for this metadata
    bool         _IsMain;        //!< if true, display on main metadata editor GUI, else in secondary

  public:
    // Public const accessors
    const std::string&  Key()           const { return _Key;           } //!< Identifier
    const std::string&  DefaultValue()  const { return _DefaultValue;  } //!< default value
    const std::string&  DisplayName()   const { return _DisplayName;   } //!< displayed as this in editors
    const std::string&  DisplayPrompt() const { return _DisplayPrompt; } //!< phrase displayed in editors when prompted to enter value (currently only for strings)
    int                 Offset()        const { return _Offset;        } //!< Offset of the real field in the target Metadata structure
    Type                Iype()          const { return _Iype;          } //!< Datatype
    bool                IsStatistic()   const { return _IsStatistic;   } //!< if true, ignore scraper values for this metadata
    bool                IsMain()        const { return _IsMain;        } //!< if true, display on main metadata editor GUI, else in secondary

    //! Constructor
    MetadataFieldDescriptor(const std::string& key,
                            const std::string& defaultValue,
                            const std::string& displayName,
                            const std::string& displayPrompt,
                            int                offset,
                            Type               type,
                            bool               isStatistic,
                            bool               isMain)
      : _Key(key),
        _DefaultValue(defaultValue),
        _DisplayName(displayName),
        _DisplayPrompt(displayPrompt),
        _Offset(offset),
        _Iype(type),
        _IsStatistic(isStatistic),
        _IsMain(isMain)
    {
    }
};

