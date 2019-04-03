package com.mapbox.mapboxsdk.testapp.maps

import android.support.test.rule.ActivityTestRule
import android.support.test.runner.AndroidJUnit4
import com.mapbox.mapboxsdk.maps.MapView
import com.mapbox.mapboxsdk.maps.MapboxMap
import com.mapbox.mapboxsdk.maps.Style
import com.mapbox.mapboxsdk.testapp.R
import com.mapbox.mapboxsdk.testapp.activity.espresso.EspressoTestActivity
import junit.framework.Assert.assertEquals
import junit.framework.Assert.assertTrue
import org.junit.Rule
import org.junit.Test
import org.junit.runner.RunWith
import java.util.concurrent.CountDownLatch

@RunWith(AndroidJUnit4::class)
class ImageMissingTest {

  @Rule
  @JvmField
  var rule = ActivityTestRule(EspressoTestActivity::class.java)

  private lateinit var mapView: MapView
  private val latch = CountDownLatch(1)
  private var imageMissingExecuted = false

  @Test
  fun testMissingImage() {
    rule.runOnUiThread {
      initialiseMap()
    }
    latch.await()
    assertTrue(imageMissingExecuted)
  }

  private fun initialiseMap() {
    mapView = rule.activity.findViewById(R.id.mapView)
    mapView.addOnStyleImageMissingListener {
      imageMissingExecuted = true
      assertEquals("missing-icon", it)
    }
    mapView.addOnDidFinishRenderingFrameListener {
      if (it) {
        latch.countDown()
      }
    }
    mapView.getMapAsync {
      it.setStyle(Style.Builder().fromJson(
        """
{
  "version": 8,
  "name": "Mapbox Streets",
  "sprite": "mapbox://sprites/mapbox/streets-v8",
  "glyphs": "mapbox://fonts/mapbox/{fontstack}/{range}.pbf",
  "sources": {
    "point": {
      "type": "geojson",
      "data": {
        "type": "Feature",
        "properties": {},
        "geometry": {
          "type": "Point",
          "coordinates": [0, 0]
        }
      }
    }
  },
  "layers": [{
    "id": "bg",
    "type": "background",
    "paint": {
      "background-color": "#f00"
    }
  }, {
    "id": "point",
    "type": "circle",
    "source": "point",
    "paint": {
      "circle-radius": 100
    }
  }, {
    "id": "icon",
    "type": "symbol",
    "source": "point",
    "layout": {
      "icon-image": "missing-icon"
    }
  }]
}
      """
      ))
    }
  }
}