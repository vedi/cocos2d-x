//
// Created by Fedor Shubin on 8/17/13.
//


#include "L12n.h"
#include "JsonHelper.h"

static L12n *sSharedL12n = NULL;

L12n *L12n::sharedL12n() {
    if (sSharedL12n == NULL) {
        sSharedL12n = new L12n();
        if (sSharedL12n->init()) {
            return sSharedL12n;
        }
        CC_ASSERT(false);
    }

    return sSharedL12n;
}

L12n::L12n():
    mMessageDict(NULL)
{}

CCDictionary *L12n::merge(CCDictionary *destDict, CCDictionary *sourceDict) {
    CCDictElement* element;
    CCDICT_FOREACH(sourceDict, element) {
            if (!destDict->objectForKey(element->getStrKey())) {
                destDict->setObject(element->getObject(), element->getStrKey());
            }
        }

    return destDict;
}

bool L12n::init() {
    std::string localizedFileName("messages/messages");
    localizedFileName.append("_").append(getLangPrefix(
            CCApplication::sharedApplication()->getCurrentLanguage()));
    localizedFileName.append(".json");
    CCDictionary *langDict = loadMessagesFromFile(localizedFileName.c_str());

    CCDictionary *defaultDict = loadMessagesFromFile("messages/messages.json");

    langDict = this->merge(langDict, defaultDict);
    
    this->setMessageDict(langDict);

    return true;
}

string L12n::getString(const char *key) {
    CCString *messageValue = (CCString *) mMessageDict->valueForKey(key);
    if (messageValue) {
        return messageValue->getCString();
    } else {
        CCLog("Unknown key %s", key);
        return key;
    }
}

CCDictionary * L12n::loadMessagesFromFile(char const *fileName) {
    std::string sFileName = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);

    if (sFileName.compare(fileName) != 0) {
        CCString *pJsonData = cocos2d::CCString::createWithContentsOfFile(sFileName.c_str());

        json_error_t jerror;
        json_t *jsonMetadata = json_loads(pJsonData->getCString(), 0, &jerror);

        if (jsonMetadata) {

            CCDictionary *messageDict = dynamic_cast<CCDictionary *>(JsonHelper::getCCObjectFromJson(jsonMetadata));
            CC_ASSERT(messageDict);

            if (jsonMetadata) {
                json_decref(jsonMetadata);
            }

            return messageDict;
        } else {
            CCLog("error: on line %d: %s\n", jerror.line, jerror.text);
            CC_ASSERT(jsonMetadata);
        }
    }
    return CCDictionary::create();
}

char const *L12n::getLangPrefix(cocos2d::LanguageType languageType) {
    char const * ret;
    if (languageType == kLanguageEnglish) {
        ret = "en";
    } else if (languageType == kLanguageChinese) {
        ret = "zh";
    } else if (languageType == kLanguageFrench) {
        ret = "fr";
    } else if (languageType == kLanguageItalian) {
        ret = "it";
    } else if (languageType == kLanguageGerman) {
        ret = "de";
    } else if (languageType == kLanguageSpanish) {
        ret = "es";
    } else if (languageType == kLanguageRussian) {
        ret = "ru";
    } else if (languageType == kLanguageKorean) {
        ret = "kr";
    } else if (languageType == kLanguageJapanese) {
        ret = "jp";
    } else if (languageType == kLanguageJapanese) {
        ret = "jp";
    } else if (languageType == kLanguageHungarian) {
        ret = "hu";
    } else if (languageType == kLanguagePortuguese) {
        ret = "pt";
    } else if (languageType == kLanguageArabic) {
        ret = "ar";
    } else {
        ret = "";
    }

    return ret;
}

