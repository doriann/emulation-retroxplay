#pragma once

#include <boost/property_tree/ptree.hpp>
#include "datetime/DateTime.h"

// Forward declaration (MetadataFieldDescriptor must indlude MetadataDescriptor)
class MetadataFieldDescriptor;

class MetadataDescriptor
{
  public:
    //! Metadata type
    enum class Type : char
    {
      Game,
      Folder,
    };

  private:
    //! Default value storage for fast dafault detection
    static MetadataDescriptor _Default;

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
    bool        _Dirty;        //!< Dirty flag (modified data flag)

    Type        _Type;         //!< Metadata type

    static MetadataDescriptor BuildDefaultValueMetadataDescriptor();

    /*!
     * Return the first static internal field descriptor reference
     * @param count Number of actual field descriptor available
     * @return first static internal field descriptor reference
     */
    static const MetadataFieldDescriptor* GetMetadataFieldDescriptors(int& count);

    static std::string FloatToString(float source, int precision);
    /*!
     * Convert integer range to string: low-high
     * @param range Integer range: Highest into MSB, Lowest into LSB
     * @return Converted string
     */
    static std::string IntToRange(int range);
    /*!
     * Convert a range X-Y to an int: Highest into MSB, Lowest into LSB (allow sorting by highest value)
     * @param range Range string
     * @param to destination int
     * @return True if the operation is successful. False otherwise.
     */
    static bool RangeToInt(const std::string& range, int& to);
    /*!
     * Convert int32 to Hexadecimal string
     * @param from Int32 value to convert to string
     * @param to Hexadecimal result string
     * @return True if the operation is successful. False otherwise.
     */
    static bool IntToHex(int from, std::string& to);
    /*!
     * Convert Hexa string into int32
     * @param from Hexadecimal string
     * @param to Target int32
     * @return True if the operation is successful. False otherwise.
     */
    static bool HexToInt(const std::string& from, int& to);
    /*!
     * Fast string to int conversion
     * @param from source string
     * @param to destination int
     * @param offset offset in source string
     * @param stop Stop char
     * @return True if the operation is successful. False otherwise.
     */
    static bool StringToInt(const std::string& from, int& to, int offset, char stop);
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
    MetadataDescriptor(const std::string& defaultName)
      : _Name(defaultName),
        _Dirty(false)
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
    bool Deserialize(const TreeNode& from, const std::string& relativeTo);

    /*!
     * Serialize internal data to XML node
     * @param relativeTo Root path
     * @return Serialized XML node
     */
    TreeNode Serialize(const std::string& relativeTo) const;

    /*!
     * Merge value from the source metadata object into the current object
     * current fields ate replaced only if they have their default value.
     * @param source Metadata object from which to merge data
     */
    void Merge(const MetadataDescriptor& source);

    /*
     * Accessors
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

    /*
     * Defaults
     */

    bool IsDefaultName()            const { return _Default._Name        == _Name;        }
    bool IsDefaultEmulator()        const { return _Default._Emulator    == _Emulator;    }
    bool IsDefaultCore()            const { return _Default._Core        == _Core;        }
    bool IsDefaultRatio()           const { return _Default._Ratio       == _Ratio;       }
    bool IsDefaultDescription()     const { return _Default._Description == _Description; }
    bool IsDefaultImage()           const { return _Default._Image       == _Image;       }
    bool IsDefaultThumbnail()       const { return _Default._Thumbnail   == _Thumbnail;   }
    bool IsDefaultDevelopper()      const { return _Default._Developper  == _Developper;  }
    bool IsDefaultPublisher()       const { return _Default._Publisher   == _Publisher;   }
    bool IsDefaultGenre()           const { return _Default._Genre       == _Genre;       }
    bool IsDefaultRegion()          const { return _Default._Region      == _Region;      }
    bool IsDefaultRomType()         const { return _Default._RomType     == _RomType;     }
    bool IsDefaultRating()          const { return _Default._Rating      == _Rating;      }
    bool IsDefaultPlayerRange()     const { return _Default._Players     == _Players;     }
    bool IsDefaultReleaseDateEpoc() const { return _Default._ReleaseDate == _ReleaseDate; }
    bool IsDefaultPlayCount()       const { return _Default._Playcount   == _Playcount;   }
    bool IsDefaultLastPlayedEpoc()  const { return _Default._LastPlayed  == _LastPlayed;  }
    bool IsDefaultRomCrc32()        const { return _Default._RomCrc32    == _RomCrc32;    }
    bool IsDefaultFavorite()        const { return _Default._Favorite    == _Favorite;    }
    bool IsDefaultHidden()          const { return _Default._Hidden      == _Hidden;      }

    /*
     * Convenient Accessors
     */

    bool IsGame()   const { return _Type == Type::Game;   }
    bool IsFolder() const { return _Type == Type::Folder; }
    bool IsDirty()  const { return _Dirty;                }

    std::string PlayersAsString() const { return IntToRange(_Players); }
    std::string FavoriteAsString() const { return _Favorite ? "true" : "false"; }
    std::string RatingAsString() const { return FloatToString(_Rating, 4); }

    /*
     * Convenient Methods
     */

    static bool AreGames(const MetadataDescriptor& md1, const MetadataDescriptor& md2) { return (md1._Type == md2._Type) && (md1._Type == Type::Game); }
    static bool AreFolders(const MetadataDescriptor& md1, const MetadataDescriptor& md2) { return (md1._Type == md2._Type) && (md1._Type == Type::Folder); }

    /*
     * Modifiers
     */

    void IncPlaycount() { _Playcount++; _Dirty = true; }
    void SetLastplayedNow() { _LastPlayed = DateTime().ToEpochTime(); _Dirty = true; }
};

