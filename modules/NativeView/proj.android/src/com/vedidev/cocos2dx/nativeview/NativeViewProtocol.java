package com.vedidev.cocos2dx.nativeview;

import org.json.JSONObject;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:37 PM
 */
public interface NativeViewProtocol {
    void sendMessageToView(String messageData);
    void close();
}
