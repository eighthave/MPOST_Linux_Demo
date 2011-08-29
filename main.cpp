
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "../MPOST_Linux/Acceptor.h"


using namespace std;
using namespace MPOST;


CAcceptor* g_acceptor = new CAcceptor;


// If you do not have GTK available, you can build a limited command-line version of this
// demo by defining USE_GTK as 0. For documentation of the command-line commands, refer to
// the code at the end of this file.
#define USE_GTK 1


#if USE_GTK

#include <cairo.h>
#include "/glib-2.16.1/glibconfig.h"
#include <glib.h>
#include <gtk/gtk.h>

GtkLayout *layout = 0;

GtkTextView *g_textView;
GtkButton *g_openButton;
GtkButton *g_closeButton;
GtkButton *g_stackButton;
GtkButton *g_returnButton;
GtkButton *g_calibrateButton;
GtkButton *g_flashDownloadButton;
GtkButton *g_capabilitiesButton;
GtkButton *g_propertiesButton;
GtkButton *g_billSetButton;
GtkButton *g_billValuesButton;
GtkButton *g_deviceInfoButton;
GtkButton *g_rawTransactionButton;
GtkWidget *g_downloadProgressBar;
GtkWidget *g_DownloadStartButton;
GtkWidget *g_DownloadCloseButton;


void ConnectedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Connected" << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Connected.\n", -1);

	gtk_widget_set_sensitive(GTK_WIDGET(g_openButton), false);	
	gtk_widget_set_sensitive(GTK_WIDGET(g_closeButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_stackButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_returnButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_calibrateButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_flashDownloadButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_capabilitiesButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_propertiesButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_billSetButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_billValuesButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_deviceInfoButton), true);
	gtk_widget_set_sensitive(GTK_WIDGET(g_rawTransactionButton), true);
}
void DisconnectedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Disconnected" << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Disconnected.\n", -1);

	gtk_widget_set_sensitive(GTK_WIDGET(g_openButton), true);	
	gtk_widget_set_sensitive(GTK_WIDGET(g_closeButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_stackButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_returnButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_calibrateButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_flashDownloadButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_capabilitiesButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_propertiesButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_billSetButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_billValuesButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_deviceInfoButton), false);
	gtk_widget_set_sensitive(GTK_WIDGET(g_rawTransactionButton), false);
}
void EscrowEventHandler(CAcceptor* g_acceptor, int value)
{
	stringstream ss;
	
	ss << "EVENT: Escrow: Doc Type: " <<  CAcceptor::DocumentTypeToString(g_acceptor->GetDocType()) << " " << g_acceptor->GetBill().ToString() << endl;
	
	cout << ss.str().c_str();
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);
	gtk_text_buffer_insert_at_cursor(textBuffer, ss.str().c_str(), -1);
}
void PUPEscrowEventHandler(CAcceptor* g_acceptor, int value)
{
	stringstream ss;
	
	ss << "EVENT: PUPEscrow: " << g_acceptor->GetBill().ToString() << endl;
	
	cout << ss.str().c_str();
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, ss.str().c_str(), -1);
}
void StackedEventHandler(CAcceptor* g_acceptor, int value)
{
	stringstream ss;
	
	ss << "EVENT: Stacked: Doc Type: " <<  CAcceptor::DocumentTypeToString(g_acceptor->GetDocType()) << " " << g_acceptor->GetBill().ToString() << endl;
	
	cout << ss.str().c_str();
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, ss.str().c_str(), -1);
}
void ReturnedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Returned." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Returned.\n", -1);
}
void RejectedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Rejected." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Rejected.\n", -1);
}
void CheatedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Cheated." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Cheated.\n", -1);
}
void StackerFullEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Stacker Full." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Stacker Full.\n", -1);
}
void CalibrateStartEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Calibrate Start." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Calibrate Start.\n", -1);
}
void CalibrateProgressEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Calibrate Progress." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Calibrate Progress.\n", -1);
}
void CalibrateFinishEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Calibrate Finish." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Calibrate Finish.\n", -1);
}

int g_TotalSectors = 0;
int g_SectorsDownloaded = 0;

void DownloadStartEventHandler(CAcceptor* g_acceptor, int value)
{
	g_TotalSectors = value;
	
	cout << "EVENT: Download Start." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Download Start.\n", -1);
}
void DownloadRestartEventHandler(CAcceptor* g_acceptor, int value)
{
	gtk_widget_set_sensitive(GTK_WIDGET(g_flashDownloadButton), true);
	
	cout << "EVENT: Download Restart." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);	
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Download Restart.\n", -1);
}
void DownloadProgressEventHandler(CAcceptor* g_acceptor, int value)
{
	g_SectorsDownloaded = value;
	
	cout << "EVENT: Download Progress." << endl;
	
//	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);
//	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Download Start.\n", -1);
	
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(g_downloadProgressBar),(double)g_SectorsDownloaded /(double)g_TotalSectors);
}
void DownloadFinishEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Download Finish." << endl;
	
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(g_textView);
	gtk_text_buffer_insert_at_cursor(textBuffer, "EVENT: Download Finish.\n", -1);

    gtk_widget_set_sensitive(GTK_WIDGET(g_DownloadCloseButton), true);		
}


void OnOpenButton(GtkButton *button, gpointer data)
{
    g_acceptor->SetEnableAcceptance(true);
    
    g_acceptor->SetDebugLog(true);

    
	GtkEntry* portNameEntry =(GtkEntry*)data;
	
	const char* portName = gtk_entry_get_text(portNameEntry);
    
    g_acceptor->Open(portName, A);
}
void OnCloseButton(GtkButton *button, gpointer data)
{
	g_acceptor->Close();
}
void OnReturnButton(GtkButton *button, gpointer data)
{
	g_acceptor->EscrowReturn();
}
void OnStackButton(GtkButton *button, gpointer data)
{
	g_acceptor->EscrowStack();
}
void OnCalibrateButton(GtkButton *button, gpointer data)
{
	g_acceptor->Calibrate();
}
void OnFlashDownloadCloseButton(GtkButton *button, gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(data));
}
void OnFlashDownloadStartButton(GtkButton *button, gpointer data)
{
    gtk_widget_set_sensitive(GTK_WIDGET(g_DownloadStartButton), false);		
	
	GtkEntry* textEntry =(GtkEntry*)data;
	
	const char* s = gtk_entry_get_text(textEntry);
	
	g_acceptor->FlashDownload(s);
}
void OnFlashDownloadButton(GtkButton *button, gpointer data)
{
    GtkWidget *dialog = gtk_dialog_new();
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);
    
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), gtk_label_new("Download File"));
	
    GtkWidget *textEntry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),textEntry);
    gtk_entry_set_text(GTK_ENTRY(textEntry), "/root/workspace/MPOST/490021211_SC83_JPY_FLASH.BIN");// "490014230_SC83_USD_FLASH.BIN");

    g_DownloadStartButton = gtk_button_new_with_label("Start");
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->action_area), g_DownloadStartButton);
    gtk_signal_connect(GTK_OBJECT(g_DownloadStartButton), "clicked", GTK_SIGNAL_FUNC(OnFlashDownloadStartButton), textEntry);
    
    g_DownloadCloseButton = gtk_button_new_with_label("Close");
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->action_area), g_DownloadCloseButton);
    gtk_widget_set_sensitive(GTK_WIDGET(g_DownloadCloseButton), false);		
    gtk_signal_connect(GTK_OBJECT(g_DownloadCloseButton), "clicked", GTK_SIGNAL_FUNC(OnFlashDownloadCloseButton), dialog);
    
    g_downloadProgressBar = gtk_progress_bar_new();
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), g_downloadProgressBar);     

    gtk_widget_show_all(dialog);
	
}
void OnCapabilitiesButton(GtkButton *button, gpointer data)
{
	GtkWidget *dialog = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog), "Capabilities");
	gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);
    
	GtkTextView *textView =(GtkTextView*)gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), GTK_WIDGET(textView));
	
	if (g_acceptor->GetConnected())
	{
		GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(textView);

		string s;

		s = "CapApplicationID: " + string((g_acceptor->GetCapApplicationID() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapApplicationPN: " + string((g_acceptor->GetCapApplicationPN() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapAssetNumber: " + string((g_acceptor->GetCapAssetNumber() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapAudit: " + string((g_acceptor->GetCapAudit() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapBarCodes: " + string((g_acceptor->GetCapBarCodes() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapBarCodesExt: " + string((g_acceptor->GetCapBarCodesExt() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapBNFStatus: " + string((g_acceptor->GetCapBNFStatus() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapBookmark: " + string((g_acceptor->GetCapBookmark() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapBootPN: " + string((g_acceptor->GetCapBootPN() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapCalibrate: " + string((g_acceptor->GetCapCalibrate() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapCashBoxTotal: " + string((g_acceptor->GetCapCashBoxTotal() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapCouponExt: " + string((g_acceptor->GetCapCouponExt() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapDevicePaused: " + string((g_acceptor->GetCapDevicePaused() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapDeviceType: " + string((g_acceptor->GetCapDeviceType() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapDeviceResets: " + string((g_acceptor->GetCapDeviceResets() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapDeviceSerialNumber: " + string((g_acceptor->GetCapDeviceSerialNumber() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapSoftReset: " + string((g_acceptor->GetCapDeviceSoftReset() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapEscrowTimeout: " + string((g_acceptor->GetCapEscrowTimeout() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapFlashDownload: " + string((g_acceptor->GetCapFlashDownload() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapNoPush: " + string((g_acceptor->GetCapNoPush() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapOrientationExt: " + string((g_acceptor->GetCapOrientationExt() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapVariantID: " + string((g_acceptor->GetCapVariantID() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);

		s = "CapVariantPN: " + string((g_acceptor->GetCapVariantPN() ? "T" : "F")) + string("\n");		
		gtk_text_buffer_insert_at_cursor(textBuffer, s.c_str(), -1);
	}
	
	gtk_widget_show_all(dialog);
}


void OnChangeOrientationComboBox(GtkComboBox *comboBox, gpointer data)
{
	switch(gtk_combo_box_get_active(comboBox))
	{
	case 0:
		g_acceptor->SetOrientationControl(FourWay);
		break;

	case 1:
		g_acceptor->SetOrientationControl(TwoWay);
		break;

	case 2:
		g_acceptor->SetOrientationControl(OneWay);
		break;
	}
}
void OnChangeOrientationExtComboBox(GtkComboBox *comboBox, gpointer data)
{
	switch(gtk_combo_box_get_active(comboBox))
	{
	case 0:
		g_acceptor->SetOrientationCtlExt(FourWay);
		break;

	case 1:
		g_acceptor->SetOrientationCtlExt(TwoWay);
		break;

	case 2:
		g_acceptor->SetOrientationCtlExt(OneWay);
		break;
	}
}
void OnChangeBezelComboBox(GtkComboBox *comboBox, gpointer data)
{
	switch(gtk_combo_box_get_active(comboBox))
	{
	case 0:
		g_acceptor->SetBezel(Standard);
		break;

	case 1:
		g_acceptor->SetBezel(Platform);
		break;

	case 2:
		g_acceptor->SetBezel(Diagnostic);
		break;
	}
}

void OnToggledDebugLogButton(GtkButton *button, gpointer data)
{
	g_acceptor->SetDebugLog(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}
void OnToggledEnableAcceptanceButton(GtkButton *button, gpointer data)
{
	g_acceptor->SetEnableAcceptance(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}
void OnToggledAutoStackButton(GtkButton *button, gpointer data)
{
	g_acceptor->SetAutoStack(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}
void OnToggledBarCodeVouchersButton(GtkButton *button, gpointer data)
{
	g_acceptor->SetEnableBarCodes(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}
void OnToggledBookmarksButton(GtkButton *button, gpointer data)
{
	g_acceptor->SetEnableBookmarks(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}
void OnToggledExtendedCouponButton(GtkButton *button, gpointer data)
{
	g_acceptor->SetEnableCouponExt(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}
void OnToggledNoPushModeButton(GtkButton *button, gpointer data)
{
	g_acceptor->SetEnableNoPush(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}
void OnToggledHighSecurityModeButton(GtkButton *button, gpointer data)
{
	g_acceptor->SetHighSecurity(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}


void OnPropertiesButton(GtkButton *button, gpointer data)
{
	GtkWidget *dialog = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog), "Properties");
	gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);
	
	
	GtkWidget *debugLogButton = gtk_check_button_new_with_label("Debug Log");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), debugLogButton);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(debugLogButton), g_acceptor->GetDebugLog());
	gtk_signal_connect(GTK_OBJECT(debugLogButton), "toggled", GTK_SIGNAL_FUNC(OnToggledDebugLogButton), NULL);
	
	GtkWidget *enableAcceptanceButton = gtk_check_button_new_with_label("Enable Acceptance");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), enableAcceptanceButton);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(enableAcceptanceButton), g_acceptor->GetEnableAcceptance());
	gtk_signal_connect(GTK_OBJECT(enableAcceptanceButton), "toggled", GTK_SIGNAL_FUNC(OnToggledEnableAcceptanceButton), NULL);
	
	GtkWidget *autoStackButton = gtk_check_button_new_with_label("Auto Stack");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), autoStackButton);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(autoStackButton), g_acceptor->GetAutoStack());
	gtk_signal_connect(GTK_OBJECT(autoStackButton), "toggled", GTK_SIGNAL_FUNC(OnToggledAutoStackButton), NULL);
	
	GtkWidget *barCodeVouchersButton = gtk_check_button_new_with_label("Bar Code Vouchers");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), barCodeVouchersButton);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(barCodeVouchersButton), g_acceptor->GetEnableBarCodes());
	gtk_signal_connect(GTK_OBJECT(barCodeVouchersButton), "toggled", GTK_SIGNAL_FUNC(OnToggledBarCodeVouchersButton), NULL);
	
	GtkWidget *bookmarksButton = gtk_check_button_new_with_label("Bookmarks");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), bookmarksButton);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(bookmarksButton), g_acceptor->GetEnableBookmarks());
	gtk_signal_connect(GTK_OBJECT(bookmarksButton), "toggled", GTK_SIGNAL_FUNC(OnToggledBookmarksButton), NULL);
	
	GtkWidget *extendedCouponButton = gtk_check_button_new_with_label("Extended Coupon");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), extendedCouponButton);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(extendedCouponButton), g_acceptor->GetEnableCouponExt());
	gtk_signal_connect(GTK_OBJECT(extendedCouponButton), "toggled", GTK_SIGNAL_FUNC(OnToggledExtendedCouponButton), NULL);
		
	GtkWidget *noPushModeButton = gtk_check_button_new_with_label("No Push Mode");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), noPushModeButton);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(noPushModeButton), g_acceptor->GetEnableNoPush());
	gtk_signal_connect(GTK_OBJECT(noPushModeButton), "toggled", GTK_SIGNAL_FUNC(OnToggledNoPushModeButton), NULL);
	
	GtkWidget *highSecurityModeButton = gtk_check_button_new_with_label("High Security Mode");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), highSecurityModeButton);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(highSecurityModeButton), g_acceptor->GetHighSecurity());
	gtk_signal_connect(GTK_OBJECT(highSecurityModeButton), "toggled", GTK_SIGNAL_FUNC(OnToggledHighSecurityModeButton), NULL);
	
	
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), gtk_label_new("Basic Orientation"));	
	GtkWidget *orientationComboBox = gtk_combo_box_new_text();	
	gtk_combo_box_append_text(GTK_COMBO_BOX(orientationComboBox), "Four way");
	gtk_combo_box_append_text(GTK_COMBO_BOX(orientationComboBox), "Two way");
	gtk_combo_box_append_text(GTK_COMBO_BOX(orientationComboBox), "One way");
	gtk_combo_box_set_active(GTK_COMBO_BOX(orientationComboBox), g_acceptor->GetOrientationControl());	
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), orientationComboBox);	
	gtk_signal_connect(GTK_OBJECT(orientationComboBox), "changed", GTK_SIGNAL_FUNC(OnChangeOrientationComboBox), NULL);
	

	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), gtk_label_new("Extended Orientation"));	
	GtkWidget *orientationExtComboBox = gtk_combo_box_new_text();	
	gtk_combo_box_append_text(GTK_COMBO_BOX(orientationExtComboBox), "Four way");
	gtk_combo_box_append_text(GTK_COMBO_BOX(orientationExtComboBox), "Two way");
	gtk_combo_box_append_text(GTK_COMBO_BOX(orientationExtComboBox), "One way");
	gtk_combo_box_set_active(GTK_COMBO_BOX(orientationExtComboBox), g_acceptor->GetOrientationCtlExt());	
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), orientationExtComboBox);	
	gtk_signal_connect(GTK_OBJECT(orientationExtComboBox), "changed", GTK_SIGNAL_FUNC(OnChangeOrientationExtComboBox), NULL);	
	

	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), gtk_label_new("Bezel"));	
	GtkWidget *bezelComboBox = gtk_combo_box_new_text();	
	gtk_combo_box_append_text(GTK_COMBO_BOX(bezelComboBox), "Standard");
	gtk_combo_box_append_text(GTK_COMBO_BOX(bezelComboBox), "Platform");
	gtk_combo_box_append_text(GTK_COMBO_BOX(bezelComboBox), "Diagnostic");
	gtk_combo_box_set_active(GTK_COMBO_BOX(bezelComboBox), 0);	
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), bezelComboBox);	
	gtk_signal_connect(GTK_OBJECT(bezelComboBox), "changed", GTK_SIGNAL_FUNC(OnChangeBezelComboBox), NULL);
	
	
	gtk_widget_show_all(dialog);
    
}

void OnToggledBillSetCheckButton(GtkButton *button, gpointer data)
{
	vector<bool> billTypeEnables = g_acceptor->GetBillTypeEnables();
	
	billTypeEnables[atoi(gtk_widget_get_name(GTK_WIDGET(button)))] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
	
	g_acceptor->SetBillTypeEnables(billTypeEnables);
}

void OnBillSetButton(GtkButton *button, gpointer data)
{
	GtkWidget *dialog = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog), "Bill Types");
	gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);
    
	GtkTable *table =(GtkTable*)gtk_table_new(36, 4, TRUE);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), GTK_WIDGET(table));
	
	gtk_table_attach_defaults(table, gtk_label_new(""), 0, 1, 0, 1);
	gtk_table_attach_defaults(table, gtk_label_new("#"), 1, 2, 0, 1);
	gtk_table_attach_defaults(table, gtk_label_new("ISO Code"), 2, 3, 0, 1);
	gtk_table_attach_defaults(table, gtk_label_new("Value"), 3, 4, 0, 1);
	gtk_table_attach_defaults(table, gtk_label_new("Attributes"), 4, 5, 0, 1);
	
	
	vector<CBill> bills = g_acceptor->GetBillTypes();
	vector<bool> billTypeEnables = g_acceptor->GetBillTypeEnables();
	
	for(unsigned i = 0; i < bills.size(); i++)
	{
		char textBuffer[16];
		stringstream attributes;
		attributes << bills[i].GetSeries() << " " << bills[i].GetType() << " " << bills[i].GetCompatibility() << " " << bills[i].GetVersion();
	
		GtkWidget* checkButton = gtk_check_button_new();
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkButton), billTypeEnables[i]);
		gtk_signal_connect(GTK_OBJECT(checkButton), "toggled", GTK_SIGNAL_FUNC(OnToggledBillSetCheckButton), NULL);
		gtk_widget_set_name(checkButton, CAcceptor::itoa(i, textBuffer, 10));
		
		gtk_table_attach_defaults(table, checkButton, 0, 1, i + 1, i + 2);
		gtk_table_attach_defaults(table, gtk_label_new(CAcceptor::itoa(i + 1, textBuffer, 10)), 1, 2, i + 1, i + 2);
		gtk_table_attach_defaults(table, gtk_label_new(bills[i].GetCountry().c_str()), 2, 3, i + 1, i + 2);
		gtk_table_attach_defaults(table, gtk_label_new(CAcceptor::itoa(bills[i].GetValue(), textBuffer, 10)), 3, 4, i + 1, i + 2);
		gtk_table_attach_defaults(table, gtk_label_new(attributes.str().c_str()), 4, 5, i + 1, i + 2);
	}
	
	
	gtk_widget_show_all(dialog);
}


void OnToggledBillValuesCheckButton(GtkButton *button, gpointer data)
{
	vector<bool> billValueEnables = g_acceptor->GetBillValueEnables();
	
	billValueEnables[atoi(gtk_widget_get_name(GTK_WIDGET(button)))] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
	
	g_acceptor->SetBillValueEnables(billValueEnables);
}

void OnBillValuesButton(GtkButton *button, gpointer data)
{
	GtkWidget *dialog = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog), "Bill Values");
	gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);
    
	GtkTable *table =(GtkTable*)gtk_table_new(36, 4, TRUE);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), GTK_WIDGET(table));
	
	gtk_table_attach_defaults(table, gtk_label_new(""), 0, 1, 0, 1);
	gtk_table_attach_defaults(table, gtk_label_new("#"), 1, 2, 0, 1);
	gtk_table_attach_defaults(table, gtk_label_new("ISO Code"), 2, 3, 0, 1);
	gtk_table_attach_defaults(table, gtk_label_new("Value"), 3, 4, 0, 1);
	gtk_table_attach_defaults(table, gtk_label_new("Attributes"), 4, 5, 0, 1);

	vector<CBill> bills = g_acceptor->GetBillValues();
	vector<bool> billValueEnables = g_acceptor->GetBillValueEnables();
	
	for(unsigned i = 0; i < bills.size(); i++)
	{
		char textBuffer[16];
		stringstream attributes;
		attributes << bills[i].GetSeries() << " " << bills[i].GetType() << " " << bills[i].GetCompatibility() << " " << bills[i].GetVersion();
	
		GtkWidget* checkButton = gtk_check_button_new();
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkButton), billValueEnables[i]);
		gtk_signal_connect(GTK_OBJECT(checkButton), "toggled", GTK_SIGNAL_FUNC(OnToggledBillValuesCheckButton), NULL);
		gtk_widget_set_name(checkButton, CAcceptor::itoa(i, textBuffer, 10));
		
		gtk_table_attach_defaults(table, checkButton, 0, 1, i + 1, i + 2);
		gtk_table_attach_defaults(table, gtk_label_new(CAcceptor::itoa(i + 1, textBuffer, 10)), 1, 2, i + 1, i + 2);
		gtk_table_attach_defaults(table, gtk_label_new(bills[i].GetCountry().c_str()), 2, 3, i + 1, i + 2);
		gtk_table_attach_defaults(table, gtk_label_new(CAcceptor::itoa(bills[i].GetValue(), textBuffer, 10)), 3, 4, i + 1, i + 2);
		gtk_table_attach_defaults(table, gtk_label_new(attributes.str().c_str()), 4, 5, i + 1, i + 2);
	}
		
	gtk_widget_show_all(dialog);
}


void OnDeviceInfoButton(GtkButton *button, gpointer data)
{
	if (!g_acceptor->GetConnected())
		return;
	
	GtkWidget *dialog = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog), "Device Info");
	gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);
	
	GtkTextView *textView =(GtkTextView*)gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), GTK_WIDGET(textView));
			
	GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(textView);

	stringstream s;

	s << "DEVICE INFO\n";
	s << "Device Type: " <<(g_acceptor->GetCapDeviceType() ? g_acceptor->GetDeviceType() : "Not supported") << "\n";
	s << "Device CRC: " << g_acceptor->GetDeviceCRC() << "\n";
	s << "Serial #: " <<(g_acceptor->GetCapDeviceSerialNumber() ? g_acceptor->GetDeviceSerialNumber() : "Not supported") << "\n";
	s << "Boot Part #: " <<(g_acceptor->GetCapBootPN() ? g_acceptor->GetBootPN() : "Not supported") << "\n";
	s << "Application PN: " <<(g_acceptor->GetCapApplicationPN() ? g_acceptor->GetApplicationPN() : "Not supported") << "\n";
	
	if (g_acceptor->GetCapVariantPN())
	{
    	s << "Variant PN: " << g_acceptor->GetVariantPN() << "\n";
    	s << "Variant Name: " << "\n";
    	
    	vector<string> names = g_acceptor->GetVariantNames();
    	
    	for(vector<string>::iterator i = names.begin(); i != names.end(); i++)
    		s << *i << " ";
    	
    	s << "\n";
	}
	else
	{
    	s << "Variant PN: Not supported\n";
    	s << "Variant Name: Not supported\n";
	}
	
	s << "Cassette: " <<(g_acceptor->GetCashBoxAttached() ? "Installed" : "Not installed") << "\n";
	s << "Cash in Cassette: ";
	if (g_acceptor->GetCapCashBoxTotal())
		s << g_acceptor->GetCashBoxTotal() << "\n";
	else
		s << "Not supported" << "\n";
	
	s << "Resets: " << g_acceptor->GetDeviceResets() << "\n";
	s << "Bill Path: " <<(g_acceptor->GetDeviceJammed() ? "Jammed" : "Clear") << "\n";
	s << "Model: " << g_acceptor->GetDeviceModel();
	
	if (g_acceptor->GetDeviceModel() >= 32)
		s << "(" <<(char)g_acceptor->GetDeviceModel() << ")" << "\n";
	else
		s << "\n";

	s << "BNFStatus: ";
	if (g_acceptor->GetCapBNFStatus())
		s << g_acceptor->GetBNFStatus() << "\n";
	else
		s << "Not supported" << "\n";
	
	if (g_acceptor->GetCapAudit())
	{
		s << "\nPEFORMANCE\n";
    	vector<int> values = g_acceptor->GetAuditLifeTimeTotals();
    	s << "Data Map: " << values[0] << "\n";
    	s << "Total Op Hours: " << values[1] << "\n";
    	s << "Total Mot Starts: " << values[2] << "\n";
    	s << "Total Escrow: " << values[3] << "\n";
    	s << "Total Recognized: " << values[4] << "\n";
    	s << "Total Validated: " << values[5] << "\n";

    	values = g_acceptor->GetAuditQP();
    	s << "Last 100: " << values[0] << "\n";
    	s << "Motor Starts: " << values[1] << "\n";
    	s << "Docs Stacked: " << values[2] << "\n";
    	s << "Docs Escrow: " << values[3] << "\n";
    	s << "Docs Recognition: " << values[4] << "\n";
    	s << "Docs Validated: " << values[5] << "\n";
    	s << "Docs Rec Reject: " << values[6] << "\n";
    	s << "Docs Sec Reject: " << values[7] << "\n";
    	s << "Docs Orient Reject: " << values[8] << "\n";
    	s << "Docs Disabled Reject: " << values[9] << "\n";
    	s << "Docs FF Reject: " << values[10] << "\n";
    	s << "Docs While Disabled: " << values[11] << "\n";
    	s << "Docs Host Reject: " << values[12] << "\n";
    	s << "Docs Barcode: " << values[13] << "\n";

    	values = g_acceptor->GetAuditPerformance();
    	s << "CC0 Reject: " << values[0] << "\n";
    	s << "CC1 Reject: " << values[1] << "\n";
    	s << "All James: " << values[2] << "\n";
    	s << "Jam Recovery: " << values[3] << "\n";
    	s << "Jam Reject: " << values[4] << "\n";
    	s << "Jam Stacker: " << values[5] << "\n";
    	s << "Jam No Recovery: " << values[6] << "\n";
    	s << "Out of Service: " << values[7] << "\n";
    	s << "Out of Order: " << values[8] << "\n";
    	s << "Operating Hours: " << values[9] << "\n";
    	s << "Doc Too Long: " << values[10] << "\n";
    	s << "Doc Tease: " << values[11] << "\n";
    	s << "Calibrations: " << values[12] << "\n";
    	s << "Resets: " << values[13] << "\n";
    	s << "Downloads: " << values[14] << "\n";
    	s << "Cassette Full: " << values[15] << "\n";
    	s << "Cassette Removed: " << values[16] << "\n";
	}
	else
	{
    	s << "\nPERFORMANCE: Not supported" << "\n";
	}


	gtk_text_buffer_insert_at_cursor(textBuffer, s.str().c_str(), -1);
	
	gtk_widget_show_all(dialog);
    
}


// NOTE
// This function obtained from here:
// http://www.codeproject.com/KB/string/hexstrtoint.aspx
int _httoi(const char *value)
{
  struct CHexMap
  {
    char chr;
    int value;
  };
  const int HexMapL = 16;
  CHexMap HexMap[HexMapL] =
  {
    {'0', 0}, {'1', 1},
    {'2', 2}, {'3', 3},
    {'4', 4}, {'5', 5},
    {'6', 6}, {'7', 7},
    {'8', 8}, {'9', 9},
    {'A', 10}, {'B', 11},
    {'C', 12}, {'D', 13},
    {'E', 14}, {'F', 15}
  };
  
  char valueCopy[32];
  
  strcpy(valueCopy, value);
  
  for(unsigned i = 0; i < strlen(valueCopy); i++)
	  valueCopy[i] = toupper(valueCopy[i]);
  
  char *s =(char*)(&valueCopy);
  int result = 0;
  if (*s == '0' && *(s + 1) == 'X') s += 2;
  bool firsttime = true;
  while(*s != '\0')
  {
    bool found = false;
    for(int i = 0; i < HexMapL; i++)
    {
       if (*s == HexMap[i].chr)
       {
        if (!firsttime) result <<= 4;
        result |= HexMap[i].value;
        found = true;
        break;
       }
    }
    if (!found) break;
    s++;
    firsttime = false;
  }

  return result;
}


void OnRawTransactionSendButton(GtkButton *button, gpointer data)
{
	GtkEntry* filenameEntry =(GtkEntry*)data;
	
	char* text =(char*)gtk_entry_get_text(filenameEntry);
	
	char commandBytes[128];
	int commandLength = 0;
	
	string command = text;
	command += " ";
	
	string byteString;
	
	for(unsigned i = 0; i < command.length(); i++)
	{
		if (command[i] != ' ')
		{
			byteString  += command[i];
		}
		else
		{
			if (byteString != "")
			{
				int b = _httoi(byteString.c_str());
				
				commandBytes[commandLength] = b;
				
				commandLength++;
				
				byteString = "";								
			}
		}		
	}
		
	g_acceptor->RawTransaction(commandBytes, commandLength);
}

void OnRawTransactionButton(GtkButton *button, gpointer data)
{
	GtkWidget *dialog = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog), "Raw Transaction");
	gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);
	
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), gtk_label_new("Enter the raw command in hexadecimal excluding the STX, length, ETX, and checksum."));	
	
	GtkWidget *textEntry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),textEntry);

	GtkWidget *sendButton = gtk_button_new_with_label("Send");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->action_area), sendButton);
	gtk_signal_connect(GTK_OBJECT(sendButton), "clicked", GTK_SIGNAL_FUNC(OnRawTransactionSendButton), textEntry);
	    
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), gtk_label_new("Reply"));	

	GtkWidget *textEntry2 = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),textEntry2);

	gtk_widget_show_all(dialog);
}


#endif



static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data)
{
	if (g_acceptor->GetConnected())
		g_acceptor->Close();
	
    gtk_main_quit();
}




int main(int argc, char *argv[])
{
    g_acceptor->SetEventHandler(ConnectedEvent, ConnectedEventHandler);
    g_acceptor->SetEventHandler(DisconnectedEvent, DisconnectedEventHandler);
    g_acceptor->SetEventHandler(EscrowEvent, EscrowEventHandler);
    g_acceptor->SetEventHandler(PUPEscrowEvent, PUPEscrowEventHandler);
    g_acceptor->SetEventHandler(StackedEvent, StackedEventHandler);
    g_acceptor->SetEventHandler(ReturnedEvent, ReturnedEventHandler);
    g_acceptor->SetEventHandler(RejectedEvent, RejectedEventHandler);
    g_acceptor->SetEventHandler(CheatedEvent, CheatedEventHandler);
    g_acceptor->SetEventHandler(StackerFullEvent, StackerFullEventHandler);
    g_acceptor->SetEventHandler(CalibrateStartEvent, CalibrateStartEventHandler);
    g_acceptor->SetEventHandler(CalibrateProgressEvent, CalibrateProgressEventHandler);
    g_acceptor->SetEventHandler(CalibrateFinishEvent, CalibrateFinishEventHandler);
    g_acceptor->SetEventHandler(DownloadStartEvent, DownloadStartEventHandler);
    g_acceptor->SetEventHandler(DownloadRestartEvent, DownloadRestartEventHandler);
    g_acceptor->SetEventHandler(DownloadProgressEvent, DownloadProgressEventHandler);
    g_acceptor->SetEventHandler(DownloadFinishEvent, DownloadFinishEventHandler);
    
#if USE_GTK
	GtkWidget *window;

    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "M/POST Linux Demo");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 760);

    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    gtk_widget_show(window);
 
    layout = GTK_LAYOUT(gtk_layout_new(NULL, NULL));
    gtk_widget_show(GTK_WIDGET(layout));
    

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(layout));  


    
    GtkWidget* scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    g_textView =(GtkTextView*)gtk_text_view_new();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_WIDGET(g_textView));       
    gtk_layout_put(layout, GTK_WIDGET(scrolledWindow), 0, 0);  
	gtk_widget_set_size_request(GTK_WIDGET(scrolledWindow), 500, 190);
    

    GtkWidget *portNameEntry = gtk_entry_new();
    gtk_layout_put(layout, gtk_label_new("Port"), 0, 120);  
    gtk_layout_put(layout, GTK_WIDGET(portNameEntry), 0, 200);  
    gtk_widget_show(GTK_WIDGET(portNameEntry));
    gtk_entry_set_text(GTK_ENTRY(portNameEntry), "/dev/ttyS0");
    
    
    
    g_openButton = GTK_BUTTON(gtk_button_new_with_label("Open"));
    gtk_signal_connect(GTK_OBJECT(g_openButton), "pressed", GTK_SIGNAL_FUNC(OnOpenButton), portNameEntry);
    gtk_layout_put(layout, GTK_WIDGET(g_openButton), 0, 230);  
    
    
    g_closeButton = GTK_BUTTON(gtk_button_new_with_label("Close"));
    gtk_signal_connect(GTK_OBJECT(g_closeButton), "pressed", GTK_SIGNAL_FUNC(OnCloseButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_closeButton), 0, 260);
    gtk_widget_set_sensitive(GTK_WIDGET(g_closeButton), false);
    
    
    g_stackButton = GTK_BUTTON(gtk_button_new_with_label("Stack"));
    gtk_signal_connect(GTK_OBJECT(g_stackButton), "pressed", GTK_SIGNAL_FUNC(OnStackButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_stackButton), 0 ,290);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_stackButton), false);
    

    g_returnButton = GTK_BUTTON(gtk_button_new_with_label("Return"));
    gtk_signal_connect(GTK_OBJECT(g_returnButton), "pressed", GTK_SIGNAL_FUNC(OnReturnButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_returnButton), 0 ,320);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_returnButton), false);

    
    g_calibrateButton = GTK_BUTTON(gtk_button_new_with_label("Calibrate"));
    gtk_signal_connect(GTK_OBJECT(g_calibrateButton), "pressed", GTK_SIGNAL_FUNC(OnCalibrateButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_calibrateButton), 0, 350);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_calibrateButton), false);
    
    
    g_flashDownloadButton = GTK_BUTTON(gtk_button_new_with_label("Flash Download"));
    gtk_signal_connect(GTK_OBJECT(g_flashDownloadButton), "pressed", GTK_SIGNAL_FUNC(OnFlashDownloadButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_flashDownloadButton), 0, 380);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_flashDownloadButton), false);
    
    
    g_capabilitiesButton = GTK_BUTTON(gtk_button_new_with_label("Capabilities"));
    gtk_signal_connect(GTK_OBJECT(g_capabilitiesButton), "pressed", GTK_SIGNAL_FUNC(OnCapabilitiesButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_capabilitiesButton), 0, 430);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_capabilitiesButton), false);
    
    
    g_propertiesButton = GTK_BUTTON(gtk_button_new_with_label("Properties"));
    gtk_signal_connect(GTK_OBJECT(g_propertiesButton), "pressed", GTK_SIGNAL_FUNC(OnPropertiesButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_propertiesButton), 0, 460);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_propertiesButton), false);
    
    
    g_billSetButton = GTK_BUTTON(gtk_button_new_with_label("Bill Set"));
    gtk_signal_connect(GTK_OBJECT(g_billSetButton), "pressed", GTK_SIGNAL_FUNC(OnBillSetButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_billSetButton), 0, 490);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_billSetButton), false);
    
    
    g_billValuesButton = GTK_BUTTON(gtk_button_new_with_label("Bill Values"));
    gtk_signal_connect(GTK_OBJECT(g_billValuesButton), "pressed", GTK_SIGNAL_FUNC(OnBillValuesButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_billValuesButton), 0, 520);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_billValuesButton), false);
    
    
    g_deviceInfoButton = GTK_BUTTON(gtk_button_new_with_label("Device Info"));
    gtk_signal_connect(GTK_OBJECT(g_deviceInfoButton), "pressed", GTK_SIGNAL_FUNC(OnDeviceInfoButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_deviceInfoButton), 0, 550);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_deviceInfoButton), false);
    
    
    g_rawTransactionButton = GTK_BUTTON(gtk_button_new_with_label("Raw Transaction"));
    gtk_signal_connect(GTK_OBJECT(g_rawTransactionButton), "pressed", GTK_SIGNAL_FUNC(OnRawTransactionButton), 0);
    gtk_layout_put(layout, GTK_WIDGET(g_rawTransactionButton), 0, 580);  
    gtk_widget_set_sensitive(GTK_WIDGET(g_rawTransactionButton), false);
    
    gtk_widget_show_all(window);
    
    gtk_main();
    

// This command-line code can be used to test basic acceptor functionality.
#else // USE_GTK = 0
    string s;
    
    while(true)
    {
        cin >> s;
        
        if (s == "o")
        	g_acceptor->Open("/dev/ttyS0", A);
        
        if (s == "c")
        	g_acceptor->Close();
        
        // Exit
        if (s == "x")
        	break;
        
        if (s == "r")
        	g_acceptor->EscrowReturn();
        
        if (s == "s")
        	g_acceptor->EscrowStack();    
        
        if (s == "res")
        	g_acceptor->SoftReset();    
        
        // Hard-code the appropriate filename here (or add code to read a filename).
        if (s == "f")
        	g_acceptor->FlashDownload("/root/workspace/MPOST/284us281.bds");//490021211_SC83_JPY_FLASH.BIN");
        
        // Device Information
        if (s == "i")
        {
        	cout << "     Device Type: " <<(g_acceptor->GetCapDeviceType() ? g_acceptor->GetDeviceType() : "Not supported") << endl;
        	cout << "       Device CRC: " << g_acceptor->GetDeviceCRC() << endl;
        	cout << "        Serial #: " <<(g_acceptor->GetCapDeviceSerialNumber() ? g_acceptor->GetDeviceSerialNumber() : "Not supported") << endl;
        	cout << "     Boot Part #: " <<(g_acceptor->GetCapBootPN() ? g_acceptor->GetBootPN() : "Not supported") << endl;
        	cout << "  Application PN: " <<(g_acceptor->GetCapApplicationPN() ? g_acceptor->GetApplicationPN() : "Not supported") << endl;
        	if (g_acceptor->GetCapVariantPN())
        	{
	        	cout << "       Variant PN: " << g_acceptor->GetVariantPN() << endl;
	        	cout << "    Variant Name: " << endl;
	        	
	        	vector<string> names = g_acceptor->GetVariantNames();
	        	
	        	for(vector<string>::iterator i = names.begin(); i != names.end(); i++)
	        		cout << *i << " ";
	        	
	        	cout << endl;
        	}
        	else
        	{
	        	cout << "       Variant PN: Not supported";
	        	cout << "    Variant Name: Not supported" << endl;
        	}
        	
        	cout << "        Cassette: " <<(g_acceptor->GetCashBoxAttached() ? "Installed" : "Not installed") << endl;
        	cout << "Cash in Cassette: ";
        	if (g_acceptor->GetCapCashBoxTotal())
        		cout << g_acceptor->GetCashBoxTotal() << endl;
        	else
        		cout << "Not supported" << endl;
        	
        	cout << "           Resets: " << g_acceptor->GetDeviceResets() << endl;
        	cout << "        Bill Path: " <<(g_acceptor->GetDeviceJammed() ? "Jammed" : "Clear") << endl;
        	cout << "            Model: " << g_acceptor->GetDeviceModel();
        	
        	if (g_acceptor->GetDeviceModel() >= 32)
        		cout << "(" <<(char)g_acceptor->GetDeviceModel() << ")" << endl;
        	else
        		cout << endl;
        
        	cout << "        BNFStatus: ";
        	if (g_acceptor->GetCapBNFStatus())
        		cout << g_acceptor->GetBNFStatus() << endl;
        	else
        		cout << "Not supported" << endl;
        	
        	if (g_acceptor->GetCapAudit())
        	{
	        	vector<int> values = g_acceptor->GetAuditLifeTimeTotals();
	        	cout << "             Data Map: " << values[0] << endl;
	        	cout << "       Total Op Hours: " << values[1] << endl;
	        	cout << "    Total Mot Starts: " << values[2] << endl;
	        	cout << "        Total Escrow: " << values[3] << endl;
	        	cout << "    Total Recognized: " << values[4] << endl;
	        	cout << "     Total Validated: " << values[5] << endl;

	        	values = g_acceptor->GetAuditQP();
	        	cout << "             Last 100: " << values[0] << endl;
	        	cout << "        Motor Starts: " << values[1] << endl;
	        	cout << "        Docs Stacked: " << values[2] << endl;
	        	cout << "          Docs Escrow: " << values[3] << endl;
	        	cout << "    Docs Recognition: " << values[4] << endl;
	        	cout << "       Docs Validated: " << values[5] << endl;
	        	cout << "     Docs Rec Reject: " << values[6] << endl;
	        	cout << "     Docs Sec Reject: " << values[7] << endl;
	        	cout << "  Docs Orient Reject: " << values[8] << endl;
	        	cout << "Docs Disabled Reject: " << values[9] << endl;
	        	cout << "       Docs FF Reject: " << values[10] << endl;
	        	cout << " Docs While Disabled: " << values[11] << endl;
	        	cout << "    Docs Host Reject: " << values[12] << endl;
	        	cout << "        Docs Barcode: " << values[13] << endl;

	        	values = g_acceptor->GetAuditPerformance();
	        	cout << "           CC0 Reject: " << values[0] << endl;
	        	cout << "           CC1 Reject: " << values[1] << endl;
	        	cout << "            All James: " << values[2] << endl;
	        	cout << "        Jam Recovery: " << values[3] << endl;
	        	cout << "           Jam Reject: " << values[4] << endl;
	        	cout << "          Jam Stacker: " << values[5] << endl;
	        	cout << "     Jam No Recovery: " << values[6] << endl;
	        	cout << "       Out of Service: " << values[7] << endl;
	        	cout << "        Out of Order: " << values[8] << endl;
	        	cout << "     Operating Hours: " << values[9] << endl;
	        	cout << "        Doc Too Long: " << values[10] << endl;
	        	cout << "            Doc Tease: " << values[11] << endl;
	        	cout << "        Calibrations: " << values[12] << endl;
	        	cout << "               Resets: " << values[13] << endl;
	        	cout << "            Downloads: " << values[14] << endl;
	        	cout << "        Cassette Full: " << values[15] << endl;
	        	cout << "    Cassette Removed: " << values[16] << endl;
        	}
        	else
        	{
             	cout << "          Performance: Not supported" << endl;
        	}
        }
        
        if (s == "d")
        	g_acceptor->SetDebugLog(!g_acceptor->GetDebugLog());
    }
#endif  
        
    
	return 1;
  
}

