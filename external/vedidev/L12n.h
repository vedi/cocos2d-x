//
// Created by Fedor Shubin on 8/17/13.
//

#ifndef __L12n_H_
#define __L12n_H_

#include "vedidev/vedidev.h"

class L12n: public CCObject {
    CC_SYNTHESIZE_RETAIN(CCDictionary *, mMessageDict, MessageDict);
public:
    V_SHARED_DCL(L12n);

    virtual bool init();

    string getString(const char *key);
private:
    L12n();
    char const *getLangPrefix(LanguageType languageType);
    CCDictionary * loadMessagesFromFile(char const *fileName);

    CCDictionary *merge(CCDictionary *destDict, CCDictionary *sourceDict);
};


#endif //__L12n_H_
