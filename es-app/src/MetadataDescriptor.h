#pragma once

#include <boost/property_tree/ptree.hpp>
#include "MetadataFieldDescriptor.h"
#include "datetime/DateTime.h"

class MetadataDescriptor
{
  public:
    //! Metadata type
    enum class  Type
    {
      Game,
      Folder,
    };

  private:
    //! Game node <game></game>
    static const std::string GameNodeIdentifier;
    //! Folder node <folder></folder>
    static const std::string FolderNodeIdentifier;

    // Please keep field ordered by typpe size to reduce alignment padding
    std::string _Name;         //!< Name as simple string
    std::string _Emulator;     //!< Specific emulator
    std::string _Core;         //!< Specific core
    std::string _Ratio;        //!< Specific screen ratio
    std::string _Description;  //!< Description, multiline text
    std::string _Image;        //!< Image path
    std::string _Thumbnail;    //!< Thumbnail path
    std::string _Developper;   //!< Developper name
    std::string _Publisher;    //!< Publisher name
    std::string _Genre;        //!< Genres, comma separated
    std::string _Region;       //!< Rom/Game Region
    std::string _RomType;      //!< Rom Type (???)
    float       _Rating;       //!< Rating from 0.0 to 1.0
    int         _Players;      //!< Players range: LSW:from - MSW:to (allow sorting by max players)
    int         _ReleaseDate;  //!< Release data (epoch)
    int         _Playcount;    //!< Play counter
    int         _LastPlayed;   //!< Last time played (epoch)
    int         _RomCrc32;     //!< Rom Crc32
    bool        _Favorite;     //!< Favorite gale
    bool        _Hidden;       //!< Hidden game

    Type        _Type;         //!< Metadata type

    /*!
     * Return the first static internal field descriptor reference
     * @param count Number of actual field descriptor available
     * @return first static internal field descriptor reference
     */
    static const MetadataFieldDescriptor* GetMetadataFieldDescriptors(int& count);

    /*!
     * Convert a range X-Y to an int: Highest into MSB, Lowest into LSB (allow sorting by highest value)
     * @param range Range string
     * @param to destination int
     * @return True if the operation is successful. False otherwise.
     */
    bool RangeToInt(const std::string& range, int& to);
    /*!
     * Convert int32 to Hexadecimal string
     * @param from Int32 value to convert to string
     * @param to Hexadecimal result string
     * @return True if the operation is successful. False otherwise.
     */
    bool IntToHex(int from, std::string& to);
    /*!
     * Convert Hexa string into int32
     * @param from Hexadecimal string
     * @param to Target int32
     * @return True if the operation is successful. False otherwise.
     */
    bool HexToInt(const std::string& from, int& to);
    /*!
     * Fast string to int conversion
     * @param from source string
     * @param to destination int
     * @param offset offset in source string
     * @param stop Stop char
     * @return True if the operation is successful. False otherwise.
     */
    bool StringToInt(const std::string& from, int& to, int offset, char stop);
    /*!
     * Fast string to int conversion
     * @param from source string
     * @param to destination int
     * @return True if the operation is successful. False otherwise.
     */
    static bool StringToInt(const std::string& from, int& to);
    /*!
     * Fast string to float conversion
     * @param from source string
     * @param to destination float
     * @return True if the operation is successful. False otherwise.
     */
    static bool StringToFloat(const std::string& from, float& to);

  public:
    //! convenient ptree type access
    typedef boost::property_tree::ptree Tree;
    typedef std::pair<std::string, Tree> TreeNode;

    /*!
     * Default constructor
     */
    MetadataDescriptor()
    {
    }

    /*!
     * Copy constructor
     * @param source Source to copy data from
     */
    MetadataDescriptor(const MetadataDescriptor& source)
      : _Name        (source._Name       ),
        _Emulator    (source._Emulator   ),
        _Core        (source._Core       ),
        _Ratio       (source._Ratio      ),
        _Description (source._Description),
        _Image       (source._Image      ),
        _Thumbnail   (source._Thumbnail  ),
        _Developper  (source._Developper ),
        _Publisher   (source._Publisher  ),
        _Genre       (source._Genre      ),
        _Region      (source._Region     ),
        _RomType     (source._RomType    ),
        _Rating      (source._Rating     ),
        _Players     (source._Players    ),
        _ReleaseDate (source._ReleaseDate),
        _Playcount   (source._Playcount  ),
        _LastPlayed  (source._LastPlayed ),
        _RomCrc32    (source._RomCrc32   ),
        _Favorite    (source._Favorite   ),
        _Hidden      (source._Hidden     ),
        _Type        (source._Type       )
    {
    }

    /*!
     * Move constructor
     * @param source  Source to move data from
     */
    MetadataDescriptor(const MetadataDescriptor&& source)
      : _Name        (std::move(source._Name       )),
        _Emulator    (std::move(source._Emulator   )),
        _Core        (std::move(source._Core       )),
        _Ratio       (std::move(source._Ratio      )),
        _Description (std::move(source._Description)),
        _Image       (std::move(source._Image      )),
        _Thumbnail   (std::move(source._Thumbnail  )),
        _Developper  (std::move(source._Developper )),
        _Publisher   (std::move(source._Publisher  )),
        _Genre       (std::move(source._Genre      )),
        _Region      (std::move(source._Region     )),
        _RomType     (std::move(source._RomType    )),
        _Rating      (          source._Rating     ),
        _Players     (          source._Players    ),
        _ReleaseDate (          source._ReleaseDate),
        _Playcount   (          source._Playcount  ),
        _LastPlayed  (          source._LastPlayed ),
        _RomCrc32    (          source._RomCrc32   ),
        _Favorite    (          source._Favorite   ),
        _Hidden      (          source._Hidden     ),
        _Type        (          source._Type       )
    {
    }

    /*!
     * Deserialize data from a given Xml node
     * @param from XML Node to deserialize from
     * @param relativeTo Root path
     * @return True of the node has been successfully deserialized
     */
    bool Deserialize(const Tree& from, const std::string& relativeTo);

    /*!
     * Serialize internal data to XML node
     * @param relativeTo Root path
     * @return Serialized XML node
     */
    Tree Serialize(const std::string& relativeTo);

    /*
     * Accesors
     */

    Type Type() const { return _Type; }

    const std::string& Name()        const { return _Name;        }
    const std::string& Emulator()    const { return _Emulator;    }
    const std::string& Core()        const { return _Core;        }
    const std::string& Ratio()       const { return _Ratio;       }
    const std::string& Description() const { return _Description; }
    const std::string& Image()       const { return _Image;       }
    const std::string& Thumbnail()   const { return _Thumbnail;   }
    const std::string& Developper()  const { return _Developper;  }
    const std::string& Publisher()   const { return _Publisher;   }
    const std::string& Genre()       const { return _Genre;       }
    const std::string& Region()      const { return _Region;      }
    const std::string& RomType()     const { return _RomType;     }

    float              Rating()          const { return _Rating; }
    int                PlayerRange()     const { return _Players; }
    int                PlayerMax()       const { return _Players >> 16; }
    int                PlayerMin()       const { return _Players & 0xFFFF; }
    int                ReleaseDateEpoc() const { return _ReleaseDate; }
    DateTime           ReleaseDate()     const { return std::move(DateTime((long long)_ReleaseDate)); }
    int                PlayCount()       const { return _Playcount; }
    int                LastPlayedEpoc()  const { return _LastPlayed; }
    DateTime           LastPlayed()      const { return std::move(DateTime((long long)_LastPlayed)); }
    int                RomCrc32()        const { return _RomCrc32; }
    bool               Favorite()        const { return _Favorite; }
    bool               Hidden()          const { return _Hidden; }
};
