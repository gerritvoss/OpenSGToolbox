#include "OSGGStreamerManager.h"

#include <gst/gst.h>
#include <iostream>


OSG_BEGIN_NAMESPACE

GStreamerManager *GStreamerManager::_the = NULL;

GStreamerManager *GStreamerManager::the(void)
{
    if(_the == NULL)
        _the = new GStreamerManager;

    return _the;
}

void GStreamerManager::init(int   argc, char *argv[])
{
    const gchar *nano_str;
    guint major, minor, micro, nano;

    gst_init (&argc, &argv);

    gst_version (&major, &minor, &micro, &nano);

    if (nano == 1)
    nano_str = "(CVS)";
    else if (nano == 2)
    nano_str = "(Prerelease)";
    else
    nano_str = "";

    std::cout << "This program is linked against GStreamer: " << major << "." << minor << "." << micro << " " << nano_str <<  std::endl; 
}

void GStreamerManager::exit(void)
{
}
static gboolean
bus_call (GstBus     *bus,
          GstMessage *msg,
          gpointer    data)
{
  GMainLoop *loop = (GMainLoop *) data;

  switch (GST_MESSAGE_TYPE (msg)) {

    case GST_MESSAGE_EOS:
      g_print ("End of stream\n");
      g_main_loop_quit (loop);
      break;

    case GST_MESSAGE_ERROR: {
      gchar  *debug;
      GError *error;

      gst_message_parse_error (msg, &error, &debug);
      g_free (debug);

      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }

  return TRUE;
}


static void
on_pad_added (GstElement *element,
              GstPad     *pad,
              gpointer    data)
{
  GstPad *sinkpad;
  GstElement *decoder = (GstElement *) data;

  /* We can now link this pad with the vorbis-decoder sink pad */
  g_print ("Dynamic pad created, linking demuxer/decoder\n");

  sinkpad = gst_element_get_static_pad (decoder, "sink");

  gst_pad_link (pad, sinkpad);

  gst_object_unref (sinkpad);
}

void GStreamerManager::openVideo(std::string Path)
{
}

void GStreamerManager::doSomething(void)
{
    GMainLoop *loop;

  GstElement *pipeline, *source, *demuxer, *decoder, *conv, *sink;
  GstBus *bus;

  /* Initialisation */
  //gst_init (&argc, &argv);

  loop = g_main_loop_new (NULL, FALSE);


  /* Check input arguments */
  //if (argc != 2) {
  //  g_printerr ("Usage: %s <Ogg/Vorbis filename>\n", argv[0]);
  //  return -1;
  //}


  /* Create gstreamer elements */
  pipeline = gst_pipeline_new ("audio-player");
  source   = gst_element_factory_make ("filesrc",       "file-source");
  demuxer  = gst_element_factory_make ("oggdemux",      "ogg-demuxer");
  decoder  = gst_element_factory_make ("vorbisdec",     "vorbis-decoder");
  conv     = gst_element_factory_make ("audioconvert",  "converter");
  //sink     = gst_element_factory_make ("autoaudiosink", "audio-output");
  sink     = gst_element_factory_make ("filesink", "audio-output");

  if (!pipeline || !source || !demuxer || !decoder || !conv || !sink) {
    g_printerr ("One element could not be created. Exiting.\n");
    return;
  }

  /* Set up the pipeline */

  /* we set the input filename to the source element */
  std::string File("K:\\Documents and Settings\\David\\My Documents\\Downloads\\Test.ogg");
  g_object_set (G_OBJECT (source), "location", File.c_str(), NULL);
  
  g_object_set (G_OBJECT (sink), "location", "Bla.raw", NULL);

  /* we add a message handler */
  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  gst_bus_add_watch (bus, bus_call, loop);
  gst_object_unref (bus);

  /* we add all elements into the pipeline */
  /* file-source | ogg-demuxer | vorbis-decoder | converter | alsa-output */
  gst_bin_add_many (GST_BIN (pipeline),
                    source, demuxer, decoder, conv, sink, NULL);

  /* we link the elements together */
  /* file-source -> ogg-demuxer ~> vorbis-decoder -> converter -> alsa-output */
  gst_element_link (source, demuxer);
  gst_element_link_many (decoder, conv, sink, NULL);
  g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_pad_added), decoder);

  /* note that the demuxer will be linked to the decoder dynamically.
     The reason is that Ogg may contain various streams (for example
     audio and video). The source pad(s) will be created at run time,
     by the demuxer when it detects the amount and nature of streams.
     Therefore we connect a callback function which will be executed
     when the "pad-added" is emitted.*/


  /* Set the pipeline to "playing" state*/
  //g_print ("Now playing: %s\n", argv[1]);
  gst_element_set_state (pipeline, GST_STATE_PLAYING);


  /* Iterate */
  g_print ("Running...\n");
  g_main_loop_run (loop);


  /* Out of the main loop, clean up nicely */
  g_print ("Returned, stopping playback\n");
  gst_element_set_state (pipeline, GST_STATE_NULL);

  g_print ("Deleting pipeline\n");
  gst_object_unref (GST_OBJECT (pipeline));

  //return 0;
}
/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

GStreamerManager::GStreamerManager(void)
{
}
    
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

GStreamerManager::~GStreamerManager(void)
{
}

OSG_END_NAMESPACE