//==============================================================================
//
//  This file is part of GNSSTk, the ARL:UT GNSS Toolkit.
//
//  The GNSSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GNSSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GNSSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin.
//  Copyright 2004-2022, The Board of Regents of The University of Texas System
//
//==============================================================================

//==============================================================================
//
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin, under contract to an agency or agencies
//  within the U.S. Department of Defense. The U.S. Government retains all
//  rights to use, duplicate, distribute, disclose, or release this software.
//
//  Pursuant to DoD Directive 523024
//
//  DISTRIBUTION STATEMENT A: This software has been approved for public
//                            release, distribution is unlimited.
//
//==============================================================================

#ifndef MERGEFRAME_HPP
#define MERGEFRAME_HPP

#include <gnsstk/BasicFramework.hpp>

/// Base class for writing utilities that merge files

class MergeFrame : public gnsstk::BasicFramework
{
public:
      /**
       * arg0 is the name of the executable from argv[0].
       * type is a string with the type of file (i.e. "RINEX Obs").
       * message is an extra message that gets passed to the
       * program description.
       */
   MergeFrame(char* arg0,
              const std::string& type,
              const std::string& message = std::string())
         : gnsstk::BasicFramework(arg0,
                                 "Sorts and merges input " + type +
                                 " files into a single file. " + message),
           inputFileOption("<" + type + " file> [...]", true),
           outputFileOption('o',
                            "output",
                            "Name for the merged output " + type + " file."
                            " Any existing file with that name will be"
                            " overwritten.",
                            true)
   {
      outputFileOption.setMaxCount(1);
   }
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverloaded-virtual"
   virtual bool initialize(int argc, char* argv[]) noexcept
   {
      return gnsstk::BasicFramework::initialize(argc, argv);
   }
#pragma clang diagnostic pop
protected:
   virtual void process() = 0;

   gnsstk::CommandOptionRest inputFileOption;
   gnsstk::CommandOptionWithAnyArg outputFileOption;
};


#endif
