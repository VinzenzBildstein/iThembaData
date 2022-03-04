#ifndef TDRTIGRESSHIT_H
#define TDRTIGRESSHIT_H

/** \addtogroup Detectors
 *  @{
 */

#include <cstdio>
#include <cmath>

#include "TVector3.h"

#include "TFragment.h"
#include "TChannel.h"

#include "TDetectorHit.h"
#include "TRunInfo.h"

class TTdrTigressHit : public TDetectorHit {
public:
   enum class ETdrTigressHitBits {
      kTotalPU1    = 1<<0,
      kTotalPU2    = 1<<1,
      kPUHitOffset = kTotalPU2,
      kPUHit1      = 1<<2,
      kPUHit2      = 1<<3,
      kBit4        = 1<<4,
      kBit5        = 1<<5,
      kBit6        = 1<<6,
      kBit7        = 1<<7
   };

public:
   TTdrTigressHit();
   TTdrTigressHit(const TTdrTigressHit&);
   TTdrTigressHit(const TFragment&);
   ~TTdrTigressHit() override;

private:
   Int_t                   fFilter{0};                  ///<  The Filter Word
   TTransientBits<UChar_t> fTdrTigressHitBits;             ///<  Transient Member Flags
   UInt_t                  fCrystal{0};                 //!<! Crystal Number
   Bool_t                  fBremSuppressed_flag{false}; //!<! Bremsstrahlung Suppression flag.

public:
   /////////////////////////  Setters	/////////////////////////////////////
   inline void SetFilterPattern(const int& x) { fFilter = x; } //!<!

   /////////////////////////  Getters	/////////////////////////////////////
   inline Int_t GetFilterPattern() const { return fFilter; } //!<!

   /////////////////////////  Recommended Functions/////////////////////////

   /////////////////////////  TChannel Helpers /////////////////////////////////////
   UShort_t NPileUps() const;
   UShort_t PUHit() const;
   void SetNPileUps(UChar_t npileups);
   void SetPUHit(UChar_t puhit);

   /////////////////////////		/////////////////////////////////////

   inline UShort_t GetArrayNumber() const override { return (4 * (GetDetector() - 1) + (GetCrystal() + 1)); } //!<!
   // returns a number 1-64 ( 1 = Detector 1 blue;  64 =  Detector 16 white; )
   Bool_t GetIsBremSuppressed() const { return fBremSuppressed_flag; }
   void SetIsBremSuppressed(const Bool_t& supp_flag) { fBremSuppressed_flag = supp_flag; }
   void MakeBremSuppressed(const Bool_t& supp_flag) { fBremSuppressed_flag |= supp_flag; }

   bool InFilter(Int_t); //!<!

   static bool CompareEnergy(const TTdrTigressHit*, const TTdrTigressHit*); //!<!
   void        Add(const TDetectorHit*) override;                               //!<!
                                                                      // Bool_t BremSuppressed(TSceptarHit*);

public:
   void Clear(Option_t* opt = "") override;       //!<!
   void Print(Option_t* opt = "") const override; //!<!
   void Copy(TObject&) const override;            //!<!
   void Copy(TObject&, bool) const override;      //!<!

   TVector3 GetPosition(double dist) const override; //!<!
   TVector3 GetPosition() const override;

private:
   void SetTdrTigressFlag(ETdrTigressHitBits, Bool_t set);
   Double_t GetDefaultDistance() const { return 110.; }

   /// \cond CLASSIMP
   ClassDefOverride(TTdrTigressHit, 1); // Information about a TDRTIGRESS Hit
   /// \endcond
};
/*! @} */
#endif
