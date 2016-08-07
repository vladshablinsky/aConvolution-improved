#ifndef _A_MY_CONVOLUTION_H
#define _A_MY_CONVOLUTION_H

#include <iostream>

/* includes */
#include <aImage.h>
//#include <bool.h>
#include "aMyGrid.h"
#include <aConvolution.h>

// STL
#include <string>
#include <vector>

/**
 * Convolution methods
 */
//#define A_CONVOLUTION    0 // Padded same convolution, i.e. the output image O has the same size as the input image I.

template<class T, class U> class aMyConvolution: public aConv<T,U> {
public:

  //! Default constructor
  aMyConvolution() {
     Init();
  };

  //! Virtual destructor.
  virtual ~aMyConvolution() {
  };

  //! Calculate the convolution of imgI and imgG. oImg = imgT*imgG
  void make(aImage<T> &imgI, aImage<T> &imgG, aImage<T> &oImg);

  //!
  virtual bool isOK() {
      return m_isOK;
  };

  //!
  virtual std::string getLastError() {
      return m_lastError;
  };

  //! Sets the notmalisation coefficient of the type U. Default norm = 1.0.
  // If norm = 0, no normalisation, if norm < 0 a 1 / (sum of kernel elements)
  // will be calculated as the coefficient.
  virtual void setNormValue(U norm) {
      m_normValue = norm;
  };

  //! Get the current or applied normalisation coefficient.
  virtual U getNormValue() {
      return m_normValue;
  };

  //! Maximal value of the output image.
  virtual void setMaxLimit(T value){
    m_maxLimit = value;
  };

  //! Get maximal value of the output image.
  virtual T getMaxLimit(){
    return m_maxLimit;
  };

  //! Minimal value of the output image.
  virtual void setMinLimit(T value){
    m_minLimit = value;
  };

  //! Get minimal value of the output image.
  virtual T getMinLimit(){
    return m_minLimit;
  };

  //! Set limits on/off
  virtual void setLimitsOn(bool on) {
     m_isLimited = on;
  };

protected:
  //! State.
  int m_isOK;

  //! Last message.
  std::string m_lastError;

  //! Normalisation value.
  U m_normValue;
  //! Max limit.
  T m_maxLimit;
  //! Min limit.
  T m_minLimit;
  //! Limit flag.
  bool m_isLimited;

 void Init( ) { // Init method
     m_normValue = (U)1.0;
     m_maxLimit  = (T)255;
     m_minLimit  = (T)0;
     m_isLimited = false;
     m_isOK      = true;
     m_lastError = "";
  };

 //! Normalise the sum and convert to the image type T.
 inline T normalise(U sum);

}; // end of MyConvolution class description

#endif //  _A_MY_CONVOLUTION_H
