package com.vedidev.cameraModule;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.json.JSONException;
import org.json.JSONObject;

import com.easyndk.AndroidNDKHelper;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;

public class CameraModule {

	public static Integer ACTION_REQUEST_CAMERA = 0;
	public static Integer ACTION_REQUEST_GALLERY = 1;

	private static Activity activity;
	
	private static Uri outputFileUri = null;
	private static String mFileName = "tempFileName.jpg";
	
	public static String getFileName() {
		return CameraModule.mFileName;
	}

	public static void setContext(Activity activity) {
		CameraModule.activity = activity;
	}
	
	public static Uri getOutputFileUri() {
		return CameraModule.outputFileUri;
	}

	public static JSONObject dispatchNDKCall(JSONObject params) {
		JSONObject retParams = new JSONObject();
		try {
			String methodName = params.getString("method");
			if (methodName.equals("getPhoto")) {			
				Intent cameraIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);	
				
				//String imageDirectoryPath = params.getString("imagesPath");
	            
	            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd'T'HHmmss");
	            String timeStamp = dateFormat.format(new Date());
	            String imageFileName = "happiStoriesPic_" + timeStamp + ".jpg";
	            mFileName = imageFileName;

	            File photo = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES), imageFileName);   
	            cameraIntent.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(photo));
	            outputFileUri = Uri.fromFile(photo);
	            Log.i("FILEPATH", outputFileUri.toString());
	            cameraIntent.putExtra(MediaStore.EXTRA_OUTPUT, outputFileUri);
	            activity.startActivityForResult(cameraIntent, 0);				
			} 
			else if (methodName.equals("getPhotoFromGallery")) {
				Intent galeryIntent = new Intent(Intent.ACTION_GET_CONTENT);
				galeryIntent.setType("image/*");
				activity.startActivityForResult(galeryIntent, ACTION_REQUEST_GALLERY);				
			} 
			else {
				throw new UnsupportedOperationException();
			}
		} 
		catch (JSONException e) {
			throw new IllegalArgumentException(e);
		}

		return retParams;
	}
	
	public static void saveImage(String picturePath) {
	    int targetW = 240;
	    int targetH = 160;
	  
	    // Get the dimensions of the bitmap
	    BitmapFactory.Options bmOptions = new BitmapFactory.Options();
	    bmOptions.inJustDecodeBounds = true;
	    BitmapFactory.decodeFile(picturePath, bmOptions);
	    int photoW = bmOptions.outWidth;
	    int photoH = bmOptions.outHeight;
	  
	    // Determine how much to scale down the image
	    int scaleFactor = Math.min(photoW/targetW, photoH/targetH);
	  
	    // Decode the image file into a Bitmap sized to fill the View
	    bmOptions.inJustDecodeBounds = false;
	    bmOptions.inSampleSize = scaleFactor;
	    bmOptions.inPurgeable = true;
	  
	    Bitmap bitmap = BitmapFactory.decodeFile(picturePath, bmOptions);
	   
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd'T'HHmmss");
        String timeStamp = dateFormat.format(new Date());
        String imageFileName = "happiStoriesPic_" + timeStamp + ".jpg";
	   File photo = new File(activity.getFilesDir(), imageFileName);
	    try {
	        FileOutputStream fos = new FileOutputStream(photo.getAbsolutePath());
	        bitmap.compress(Bitmap.CompressFormat.JPEG, 50, fos);
	        fos.flush();
	        fos.close();
	    } catch (FileNotFoundException e) {
	        Log.d("HappiStories Camera", "File not found: " + e.getMessage());
	    } catch (IOException e) {
	        Log.d("HappiStories Camera", "Error accessing file: " + e.getMessage());
	    }
	    
	    JSONObject paramList = new JSONObject();
		try {
			paramList.put("photoFileName", photo.getAbsoluteFile());
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	    AndroidNDKHelper.sendMessageWithParameters("onPhotoWasTaken", paramList);	
	}

	public static void dispatchNDKCallback(JSONObject params) {
		Log.v("camera_easyNDK Android",
				"dispatchNDKCallback: Illegal state: unexpected callback call");
	}
}
