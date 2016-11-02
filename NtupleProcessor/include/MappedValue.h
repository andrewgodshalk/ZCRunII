#ifndef GUARD_MappedValue_h
#define GUARD_MappedValue_h

/*------------------------------------------------------------------------------
   MappedValue

 Created : 2016-11-01  godshalk
 Modified: 2016-11-01  godshalk

 Class designed to map a variable from a TTree root class given the type of
 variable and the

------------------------------------------------------------------------------*/

// Standard Libraries
#include <string>
// Root Classes
#include <Rtypes.h>  // Contains definitions for Root types (Float_t, Int_t, etc.)

enum class valType { Float, Int };

class MappedValue
{
  public:
    MappedValue(std::string t = "Float_t")
    {
      // Set the type of mapped value
      if( t == "Int_t"   ) type_ = valType::Int;
      else /*default*/     type_ = valType::Float;
    }
    ~MappedValue(){}

//    double get()
    auto get() -> ()
    { // Return value of union
        switch(type_) {
          case valType::Int   : return v_.i;
          default             : return v_.f;
        }
    }

  private:
    valType type_;
    union value {
      Int_t   i;
      Float_t f;
    } v_;

};

#endif
