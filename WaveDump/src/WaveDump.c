/******************************************************************************
*
* CAEN SpA - Front End Division
* Via Vetraia, 11 - 55049 - Viareggio ITALY
* +390594388398 - www.caen.it
*
***************************************************************************//**
* \note TERMS OF USE:
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation. This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. The user relies on the
* software, documentation and results solely at his own risk.
*
*  Description:
*  -----------------------------------------------------------------------------
*  This is a demo program that can be used with any model of the CAEN's
*  digitizer family. The purpose of WaveDump is to configure the digitizer,
*  start the acquisition, read the data and write them into output files
*  and/or plot the waveforms using 'gnuplot' as an external plotting tool.
*  The configuration of the digitizer (registers setting) is done by means of
*  a configuration file that contains a list of parameters.
*  This program uses the CAENDigitizer library which is then based on the
*  CAENComm library for the access to the devices through any type of physical
*  channel (VME, Optical Link, USB, etc...). The CAENComm support the following
*  communication paths:
*  PCI => A2818 => OpticalLink => Digitizer (any type)
*  PCI => V2718 => VME => Digitizer (only VME models)
*  USB => Digitizer (only Desktop or NIM models)
*  USB => V1718 => VME => Digitizer (only VME models)
*  If you have want to sue a VME digitizer with a different VME controller
*  you must provide the functions of the CAENComm library.
*
*  -----------------------------------------------------------------------------
*  Syntax: WaveDump [ConfigFile]
*  Default config file is "WaveDumpConfig.txt"
******************************************************************************/

#define WaveDump_Release        "3.5.2_20130329"
#define WaveDump_Release_Date   "Mar 2013"
#define DBG_TIME

#include <CAENDigitizer.h>
#include "WaveDump.h"
#include "WDplot.h"
#include "fft.h"
#include "keyb.h"
#include "X742CorrectionRoutines.h"

/* Error messages */
typedef enum  {
    ERR_NONE= 0,
    ERR_CONF_FILE_NOT_FOUND,
    ERR_DGZ_OPEN,
    ERR_BOARD_INFO_READ,
    ERR_INVALID_BOARD_TYPE,
    ERR_DGZ_PROGRAM,
    ERR_MALLOC,
    ERR_RESTART,
    ERR_INTERRUPT,
    ERR_READOUT,
    ERR_EVENT_BUILD,
    ERR_HISTO_MALLOC,
    ERR_UNHANDLED_BOARD,
    ERR_OUTFILE_WRITE,

    ERR_DUMMY_LAST,
} ERROR_CODES;
static char ErrMsg[ERR_DUMMY_LAST][100] = {
    "No Error",                                         /* ERR_NONE */
    "Configuration File not found",                     /* ERR_CONF_FILE_NOT_FOUND */
    "Can't open the digitizer",                         /* ERR_DGZ_OPEN */
    "Can't read the Board Info",                        /* ERR_BOARD_INFO_READ */
    "Can't run WaveDump for this digitizer",            /* ERR_INVALID_BOARD_TYPE */
    "Can't program the digitizer",                      /* ERR_DGZ_PROGRAM */
    "Can't allocate the memory for the readout buffer", /* ERR_MALLOC */
    "Restarting Error",                                 /* ERR_RESTART */
    "Interrupt Error",                                  /* ERR_INTERRUPT */
    "Readout Error",                                    /* ERR_READOUT */
    "Event Build Error",                                /* ERR_EVENT_BUILD */
    "Can't allocate the memory fro the histograms",     /* ERR_HISTO_MALLOC */
    "Unhandled board type",                             /* ERR_UNHANDLED_BOARD */
    "Output file write error",                          /* ERR_OUTFILE_WRITE */

};


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

/* ###########################################################################
*  Functions
*  ########################################################################### */
/*! \fn      static long get_time()
*   \brief   Get time in milliseconds
*
*   \return  time in msec
*/
static long get_time()
{
    long time_ms;
#ifdef WIN32
    struct _timeb timebuffer;
    _ftime( &timebuffer );
    time_ms = (long)timebuffer.time * 1000 + (long)timebuffer.millitm;
#else
    struct timeval t1;
    struct timezone tz;
    gettimeofday(&t1, &tz);
    time_ms = (t1.tv_sec) * 1000 + t1.tv_usec / 1000;
#endif
    return time_ms;
}


/*! \fn      int GetMoreBoardNumChannels(CAEN_DGTZ_BoardInfo_t BoardInfo,  WaveDumpConfig_t *WDcfg)
*   \brief   calculate num of channels, num of bit and sampl period according to the board type
*
*   \param   BoardInfo   Board Type
*   \param   WDcfg       pointer to the config. struct
*   \return  0 = Success; -1 = unknown board type
*/
int GetMoreBoardInfo(int handle, CAEN_DGTZ_BoardInfo_t BoardInfo, WaveDumpConfig_t *WDcfg)
{
	CAEN_DGTZ_DRS4Frequency_t freq;
	int ret;
    switch(BoardInfo.FamilyCode) {
        case CAEN_DGTZ_XX724_FAMILY_CODE: WDcfg->Nbit = 14; WDcfg->Ts = 10.0; break;
        case CAEN_DGTZ_XX720_FAMILY_CODE: WDcfg->Nbit = 12; WDcfg->Ts = 4.0;  break;
        case CAEN_DGTZ_XX721_FAMILY_CODE: WDcfg->Nbit =  8; WDcfg->Ts = 2.0;  break;
        case CAEN_DGTZ_XX731_FAMILY_CODE: WDcfg->Nbit =  8; WDcfg->Ts = 2.0;  break;
        case CAEN_DGTZ_XX751_FAMILY_CODE: WDcfg->Nbit = 10; WDcfg->Ts = 1.0;  break;
        case CAEN_DGTZ_XX761_FAMILY_CODE: WDcfg->Nbit = 10; WDcfg->Ts = 0.25;  break;
        case CAEN_DGTZ_XX740_FAMILY_CODE: WDcfg->Nbit = 12; WDcfg->Ts = 16.0; break;
        case CAEN_DGTZ_XX742_FAMILY_CODE: 
        WDcfg->Nbit = 12; 
        if ((ret = CAEN_DGTZ_GetDRS4SamplingFrequency(handle, &freq)) != CAEN_DGTZ_Success) return CAEN_DGTZ_CommError;
		switch (freq) {
				case CAEN_DGTZ_DRS4_1GHz:
						WDcfg->Ts = 1.0;
					break;
				case CAEN_DGTZ_DRS4_2_5GHz:
						WDcfg->Ts = (float)0.4;
					break;
				case CAEN_DGTZ_DRS4_5GHz:
						WDcfg->Ts = (float)0.2;
					break;
		}
        break;
        default: return -1;
    }
    if (((BoardInfo.FamilyCode == CAEN_DGTZ_XX751_FAMILY_CODE) ||
         (BoardInfo.FamilyCode == CAEN_DGTZ_XX731_FAMILY_CODE) ) && WDcfg->DesMode)
        WDcfg->Ts /= 2;

    switch(BoardInfo.FamilyCode) {
        case CAEN_DGTZ_XX724_FAMILY_CODE:
        case CAEN_DGTZ_XX720_FAMILY_CODE:
        case CAEN_DGTZ_XX721_FAMILY_CODE:
        case CAEN_DGTZ_XX751_FAMILY_CODE:
        case CAEN_DGTZ_XX761_FAMILY_CODE:
        case CAEN_DGTZ_XX731_FAMILY_CODE:
            switch(BoardInfo.FormFactor) {
                case CAEN_DGTZ_VME64_FORM_FACTOR:
                case CAEN_DGTZ_VME64X_FORM_FACTOR:
                    WDcfg->Nch = 8;
                    break;
                case CAEN_DGTZ_DESKTOP_FORM_FACTOR:
                case CAEN_DGTZ_NIM_FORM_FACTOR:
                    WDcfg->Nch = 4;
                    break;
                }
            break;
        case CAEN_DGTZ_XX740_FAMILY_CODE:
            switch( BoardInfo.FormFactor) {
            case CAEN_DGTZ_VME64_FORM_FACTOR:
            case CAEN_DGTZ_VME64X_FORM_FACTOR:
                WDcfg->Nch = 64;
                break;
            case CAEN_DGTZ_DESKTOP_FORM_FACTOR:
            case CAEN_DGTZ_NIM_FORM_FACTOR:
                WDcfg->Nch = 32;
                break;
            }
            break;
        case CAEN_DGTZ_XX742_FAMILY_CODE:
            switch( BoardInfo.FormFactor) {
            case CAEN_DGTZ_VME64_FORM_FACTOR:
            case CAEN_DGTZ_VME64X_FORM_FACTOR:
                WDcfg->Nch = 36;
                break;
            case CAEN_DGTZ_DESKTOP_FORM_FACTOR:
            case CAEN_DGTZ_NIM_FORM_FACTOR:
                WDcfg->Nch = 16;
                break;
            }
            break;
        default:
            return -1;
    }
    return 0;
}


/*! \fn      int ProgramDigitizer(int handle, WaveDumpConfig_t WDcfg)
*   \brief   configure the digitizer according to the parameters read from
*            the cofiguration file and saved in the WDcfg data structure
*
*   \param   handle   Digitizer handle
*   \param   WDcfg:   WaveDumpConfig data structure
*   \return  0 = Success; negative numbers are error codes
*/
int ProgramDigitizer(int handle, WaveDumpConfig_t WDcfg, CAEN_DGTZ_BoardInfo_t BoardInfo)
{
    int i,j, ret = 0;

    /* reset the digitizer */
    ret |= CAEN_DGTZ_Reset(handle);
	if (ret != 0) {
		printf("Error: Enable to reset digitizer.\nPlease reset digitizer manually then restart the program\n");
		return -1;
	}
    /* execute generic write commands */
    for(i=0; i<WDcfg.GWn; i++)
        ret |= CAEN_DGTZ_WriteRegister(handle, WDcfg.GWaddr[i], WDcfg.GWdata[i]);

    // Set the waveform test bit for debugging
    if (WDcfg.TestPattern)
        ret |= CAEN_DGTZ_WriteRegister(handle, CAEN_DGTZ_BROAD_CH_CONFIGBIT_SET_ADD, 1<<3);
	// custom setting for X742 boards
	if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) {
		ret |= CAEN_DGTZ_SetFastTriggerDigitizing(handle,WDcfg.FastTriggerEnabled);
		ret |= CAEN_DGTZ_SetFastTriggerMode(handle,WDcfg.FastTriggerMode);
	}
    if ((BoardInfo.FamilyCode == CAEN_DGTZ_XX751_FAMILY_CODE) || (BoardInfo.FamilyCode == CAEN_DGTZ_XX731_FAMILY_CODE)) {
        ret |= CAEN_DGTZ_SetDESMode(handle, WDcfg.DesMode);
    }
    ret |= CAEN_DGTZ_SetRecordLength(handle, WDcfg.RecordLength);
    ret |= CAEN_DGTZ_SetPostTriggerSize(handle, WDcfg.PostTrigger);
    ret |= CAEN_DGTZ_SetIOLevel(handle, WDcfg.FPIOtype);
    if( WDcfg.InterruptNumEvents > 0) {
        // Interrupt handling
        if( ret |= CAEN_DGTZ_SetInterruptConfig( handle, CAEN_DGTZ_ENABLE,
                                                 VME_INTERRUPT_LEVEL, VME_INTERRUPT_STATUS_ID,
                                                 WDcfg.InterruptNumEvents, INTERRUPT_MODE)!= CAEN_DGTZ_Success) {
            printf( "\nError configuring interrupts. Interrupts disabled\n\n");
            WDcfg.InterruptNumEvents = 0;
        }
    }
    ret |= CAEN_DGTZ_SetMaxNumEventsBLT(handle, WDcfg.NumEvents);
    ret |= CAEN_DGTZ_SetAcquisitionMode(handle, CAEN_DGTZ_SW_CONTROLLED);
    ret |= CAEN_DGTZ_SetExtTriggerInputMode(handle, WDcfg.ExtTriggerMode);

    if ((BoardInfo.FamilyCode == CAEN_DGTZ_XX740_FAMILY_CODE) || (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE)){
        ret |= CAEN_DGTZ_SetGroupEnableMask(handle, WDcfg.EnableMask);
        for(i=0; i<(WDcfg.Nch/8); i++) {
            if (WDcfg.EnableMask & (1<<i)) {
				if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) {
					for(j=0; j<8; j++) {
						if (WDcfg.DCoffsetGrpCh[i][j] != -1)
							ret |= CAEN_DGTZ_SetChannelDCOffset(handle,(i*8)+j, WDcfg.DCoffsetGrpCh[i][j]);
						else
						    ret |= CAEN_DGTZ_SetChannelDCOffset(handle,(i*8)+j, WDcfg.DCoffset[i]);
						}
				}
				else {
					ret |= CAEN_DGTZ_SetGroupDCOffset(handle, i, WDcfg.DCoffset[i]);
					ret |= CAEN_DGTZ_SetGroupSelfTrigger(handle, WDcfg.ChannelTriggerMode[i], (1<<i));
					ret |= CAEN_DGTZ_SetGroupTriggerThreshold(handle, i, WDcfg.Threshold[i]);
					ret |= CAEN_DGTZ_SetChannelGroupMask(handle, i, WDcfg.GroupTrgEnableMask[i]);
				} 
                ret |= CAEN_DGTZ_SetTriggerPolarity(handle, i, WDcfg.TriggerEdge);
                
            }
        }
    } else {
        ret |= CAEN_DGTZ_SetChannelEnableMask(handle, WDcfg.EnableMask);
        for(i=0; i<WDcfg.Nch; i++) {
            if (WDcfg.EnableMask & (1<<i)) {
                ret |= CAEN_DGTZ_SetChannelDCOffset(handle, i, WDcfg.DCoffset[i]);
                ret |= CAEN_DGTZ_SetChannelSelfTrigger(handle, WDcfg.ChannelTriggerMode[i], (1<<i));
                ret |= CAEN_DGTZ_SetChannelTriggerThreshold(handle, i, WDcfg.Threshold[i]);
                ret |= CAEN_DGTZ_SetTriggerPolarity(handle, i, WDcfg.TriggerEdge);
            }
        }
    }
	if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) {
		for(i=0; i<(WDcfg.Nch/8); i++) {
			ret |= CAEN_DGTZ_SetGroupFastTriggerDCOffset(handle,i,WDcfg.FTDCoffset[i]);
			ret |= CAEN_DGTZ_SetGroupFastTriggerThreshold(handle,i,WDcfg.FTThreshold[i]);
		}
	}
    if (ret)
        printf("Warning: errors found during the programming of the digitizer.\nSome settings may not be executed\n");

    return 0;
}


/*! \fn      void CheckKeyboardCommands(WaveDumpRun_t *WDrun)
*   \brief   check if there is a key pressed and execute the relevant command
*
*   \param   WDrun:   Pointer to the WaveDumpRun_t data structure
*   \param   WDcfg:   Pointer to the WaveDumpConfig_t data structure
*   \param   BoardInfo: structure with the board info
*/
void CheckKeyboardCommands(int handle, WaveDumpRun_t *WDrun, WaveDumpConfig_t *WDcfg, CAEN_DGTZ_BoardInfo_t BoardInfo)
{
    int c = 0;

    if(!kbhit())
        return;

    c = getch();
    if ((c < '9') && (c >= '0')) {
        int ch = c-'0';
        if ((BoardInfo.FamilyCode == CAEN_DGTZ_XX740_FAMILY_CODE) || (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE)){
            if ( (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) && (WDcfg->FastTriggerEnabled == 0) && (ch == 8)) WDrun->ChannelPlotMask = WDrun->ChannelPlotMask ; else WDrun->ChannelPlotMask ^= (1 << ch);
            if (WDrun->ChannelPlotMask & (1 << ch))
                printf("Channel %d enabled for plotting\n", ch + WDrun->GroupPlotIndex*8);
            else
                printf("Channel %d disabled for plotting\n", ch + WDrun->GroupPlotIndex*8);
        } else {
            /*if( !( WDcfg->EnableMask & (1 << ch))) {
                printf("Channel %d not enabled for acquisition\n", ch);
            } else {
                WDrun->ChannelPlotMask ^= (1 << ch);
                if (WDrun->ChannelPlotMask & (1 << ch))
                    printf("Channel %d enabled for plotting\n", ch);
                else
                    printf("Channel %d disabled for plotting\n", ch);
            }*/
            WDrun->ChannelPlotMask ^= (1 << ch);
            if (WDrun->ChannelPlotMask & (1 << ch))
                printf("Channel %d enabled for plotting\n", ch);
            else
                printf("Channel %d disabled for plotting\n", ch);
        }
    } else {
        switch(c) {
            case 'g' :
                // Update the group plot index
                if ((WDcfg->EnableMask) && (WDcfg->Nch>8)) {
                    int orgPlotIndex = WDrun->GroupPlotIndex;
                    do {
                        WDrun->GroupPlotIndex = (++WDrun->GroupPlotIndex)%(WDcfg->Nch/8);
                    } while( !((1 << WDrun->GroupPlotIndex)& WDcfg->EnableMask));
                    if( WDrun->GroupPlotIndex != orgPlotIndex) {
                        printf("Plot group set to %d\n", WDrun->GroupPlotIndex);
                    }
                }
				ClearPlot();
                break;
            case 'q' :
                WDrun->Quit = 1;
                break;
            case 'R' :
                WDrun->Restart = 1;
                break;
            case 't' :
                if (!WDrun->ContinuousTrigger) {
                    CAEN_DGTZ_SendSWtrigger(handle);
                    printf("Single Software Trigger issued\n");
                }
                break;
            case 'T' :
                WDrun->ContinuousTrigger ^= 1;
                if (WDrun->ContinuousTrigger)
                    printf("Continuous trigger is enabled\n");
                else
                    printf("Continuous trigger is disabled\n");
                break;
            case 'P' :
                if (WDrun->ChannelPlotMask == 0)
                    printf("No channel enabled for plotting\n");
                else
                    WDrun->ContinuousPlot ^= 1;
                break;
            case 'p' :
                if (WDrun->ChannelPlotMask == 0)
                    printf("No channel enabled for plotting\n");
                else
                    WDrun->SinglePlot = 1;
                break;
            case 'f' :
                WDrun->PlotType = (WDrun->PlotType == PLOT_FFT) ? PLOT_WAVEFORMS : PLOT_FFT;
                WDrun->SetPlotOptions = 1;
                break;
            case 'h' :
                WDrun->PlotType = (WDrun->PlotType == PLOT_HISTOGRAM) ? PLOT_WAVEFORMS : PLOT_HISTOGRAM;
                WDrun->RunHisto = (WDrun->PlotType == PLOT_HISTOGRAM);
                WDrun->SetPlotOptions = 1;
                break;
            case 'w' :
                if (!WDrun->ContinuousWrite)
                    WDrun->SingleWrite = 1;
                break;
            case 'W' :
                WDrun->ContinuousWrite ^= 1;
                if (WDrun->ContinuousWrite)
                    printf("Continuous writing is enabled\n");
                else
                    printf("Continuous writing is disabled\n");
                break;
            case 's' :
                if (WDrun->AcqRun == 0) {
                    printf("Acquisition started\n");
                    CAEN_DGTZ_SWStartAcquisition(handle);
                    WDrun->AcqRun = 1;
                } else {
                    printf("Acquisition stopped\n");
                    CAEN_DGTZ_SWStopAcquisition(handle);
                    WDrun->AcqRun = 0;
                }
                break;
            case ' ' :
                printf("\n                            Bindkey help                                \n");
				printf("--------------------------------------------------------------------------\n");;
                printf("  [q]   Quit\n");
                printf("  [R]   Reload configuration file and restart\n");
                printf("  [s]   Start/Stop acquisition\n");
                printf("  [t]   Send a software trigger (single shot)\n");
                printf("  [T]   Enable/Disable continuous software trigger\n");
                printf("  [w]   Write one event to output file\n");
                printf("  [W]   Enable/Disable continuous writing to output file\n");
                printf("  [p]   Plot one event\n");
                printf("  [P]   Enable/Disable continuous plot\n");
                printf("  [f]   Toggle between FFT and Waveform plot\n");
                printf("  [h]   Toggle between Histogram and Waveform plot\n");
                printf("  [g]   Change the index of the group to plot (XX740 family)\n");
                printf(" [0-7]  Enable/Disable one channel on the plot\n");
                printf("        For x740 family this is the plotted group's relative channel index\n");
                printf("[SPACE] This help\n");
				printf("--------------------------------------------------------------------------\n");
                printf("Press a key to continue\n");
                getch();
                break;
            default :   break;
        }
    }
}



/*! \brief   Write the event data into the output files
*
*   \param   WDrun Pointer to the WaveDumpRun data structure
*   \param   WDcfg Pointer to the WaveDumpConfig data structure
*   \param   EventInfo Pointer to the EventInfo data structure
*   \param   Event Pointer to the Event to write
*/
int WriteOutputFiles(WaveDumpConfig_t *WDcfg, WaveDumpRun_t *WDrun, CAEN_DGTZ_EventInfo_t *EventInfo, void *Event)
{
    int ch, j, ns;
    CAEN_DGTZ_UINT16_EVENT_t  *Event16;
    CAEN_DGTZ_UINT8_EVENT_t   *Event8;

    if (WDcfg->Nbit == 8)
        Event8 = (CAEN_DGTZ_UINT8_EVENT_t *)Event;
    else
        Event16 = (CAEN_DGTZ_UINT16_EVENT_t *)Event;

    for(ch=0; ch<WDcfg->Nch; ch++) {
        int Size = (WDcfg->Nbit == 8) ? Event8->ChSize[ch] : Event16->ChSize[ch];
        if (Size <= 0) {
            continue;
        }

        // Check the file format type
        if( WDcfg->OutFileFlags& OFF_BINARY) {
            // Binary file format
            uint32_t BinHeader[6];
            BinHeader[0] = (WDcfg->Nbit == 8) ? Size + 6*sizeof(*BinHeader) : Size*2 + 6*sizeof(*BinHeader);
            BinHeader[1] = EventInfo->BoardId;
            BinHeader[2] = EventInfo->Pattern;
            BinHeader[3] = ch;
            BinHeader[4] = EventInfo->EventCounter;
            BinHeader[5] = EventInfo->TriggerTimeTag;
            if (!WDrun->fout[ch]) {
                char fname[100];
                sprintf(fname, "wave%d.dat", ch);
                if ((WDrun->fout[ch] = fopen(fname, "wb")) == NULL)
                    return -1;
            }
            if( WDcfg->OutFileFlags & OFF_HEADER) {
                // Write the Channel Header
                if(fwrite(BinHeader, sizeof(*BinHeader), 6, WDrun->fout[ch]) != 6) {
                    // error writing to file
                    fclose(WDrun->fout[ch]);
                    WDrun->fout[ch]= NULL;
                    return -1;
                }
            }
            if (WDcfg->Nbit == 8)
                ns = (int)fwrite(Event8->DataChannel[ch], 1, Size, WDrun->fout[ch]);
            else
                ns = (int)fwrite(Event16->DataChannel[ch] , 1 , Size*2, WDrun->fout[ch]) / 2;
            if (ns != Size) {
                // error writing to file
                fclose(WDrun->fout[ch]);
                WDrun->fout[ch]= NULL;
                return -1;
            }
        } else {
            // Ascii file format
            if (!WDrun->fout[ch]) {
                char fname[100];
                sprintf(fname, "wave%d.txt", ch);
                if ((WDrun->fout[ch] = fopen(fname, "w")) == NULL)
                    return -1;
            }
            if( WDcfg->OutFileFlags & OFF_HEADER) {
                // Write the Channel Header
                fprintf(WDrun->fout[ch], "Record Length: %d\n", Size);
                fprintf(WDrun->fout[ch], "BoardID: %2d\n", EventInfo->BoardId);
                fprintf(WDrun->fout[ch], "Channel: %d\n", ch);
                fprintf(WDrun->fout[ch], "Event Number: %d\n", EventInfo->EventCounter);
                fprintf(WDrun->fout[ch], "Pattern: 0x%04X\n", EventInfo->Pattern & 0xFFFF);
                fprintf(WDrun->fout[ch], "Trigger Time Stamp: %u\n", EventInfo->TriggerTimeTag);
                fprintf(WDrun->fout[ch], "DC offset (DAC): 0x%04X\n", WDcfg->DCoffset[ch] & 0xFFFF);
            }
            for(j=0; j<Size; j++) {
                if (WDcfg->Nbit == 8)
                    fprintf(WDrun->fout[ch], "%d\n", Event8->DataChannel[ch][j]);
                else
                    fprintf(WDrun->fout[ch], "%d\n", Event16->DataChannel[ch][j]);
            }
        }
        if (WDrun->SingleWrite) {
            fclose(WDrun->fout[ch]);
            WDrun->fout[ch]= NULL;
        }
    }
    return 0;

}

/*! \brief   Write the correction table of a x742 boards into the output files
*
*   \param   Filename of output file
*   \param   DataCorrection table
*/
void SaveCorrectionTable(char *outputFileName, DataCorrection_t tb) {
    char fnStr[1000];
    int ch,i,j;
    FILE *outputfile;

    strcpy(fnStr, outputFileName);
    strcat(fnStr, "_cell.txt");
    printf("Saving correction table cell values to %s\n", fnStr);
    outputfile = fopen(fnStr, "w");
    for(ch=0; ch<MAX_X742_CHANNELS+1; ch++) {
        fprintf(outputfile, "Calibration values from cell 0 to 1024 for channel %d:\n\n", ch);
        for(i=0; i<1024; i+=8) {
            for(j=0; j<8; j++)
                fprintf(outputfile, "%d\t", tb.cell[ch][i+j]);
            fprintf(outputfile, "cell = %d to %d\n", i, i+7);
        }
    }
    fclose(outputfile);

    strcpy(fnStr, outputFileName);
    strcat(fnStr, "_nsample.txt");
    printf("Saving correction table nsamples values to %s\n", fnStr);
    outputfile = fopen(fnStr, "w");
    for(ch=0; ch<MAX_X742_CHANNELS+1; ch++) {
        fprintf(outputfile, "Calibration values from cell 0 to 1024 for channel %d:\n\n", ch);
        for(i=0; i<1024; i+=8) {
            for(j=0; j<8; j++)
                fprintf(outputfile, "%d\t", tb.nsample[ch][i+j]);
            fprintf(outputfile, "cell = %d to %d\n", i, i+7);
        }
    }
    fclose(outputfile);

    strcpy(fnStr, outputFileName);
    strcat(fnStr, "_time.txt");
    printf("Saving correction table time values to %s\n", fnStr);
    outputfile = fopen(fnStr, "w");
    fprintf(outputfile, "Calibration values (ps) from cell 0 to 1024 :\n\n");
    for(i=0; i<1024; i+=8) {
        for(ch=0; ch<8; ch++)
            fprintf(outputfile, "%09.3f\t", tb.time[i+ch]);
        fprintf(outputfile, "cell = %d to %d\n", i, i+7);
    }
    fclose(outputfile);
}

/*! \brief   Write the event data on x742 boards into the output files
*
*   \param   WDrun Pointer to the WaveDumpRun data structure
*   \param   WDcfg Pointer to the WaveDumpConfig data structure
*   \param   EventInfo Pointer to the EventInfo data structure
*   \param   Event Pointer to the Event to write
*/
int WriteOutputFilesx742(WaveDumpConfig_t *WDcfg, WaveDumpRun_t *WDrun, CAEN_DGTZ_EventInfo_t *EventInfo, CAEN_DGTZ_X742_EVENT_t *Event)
{
    int gr,ch, j, ns;
    char trname[10], flag; 
	for (gr=0;gr<(WDcfg->Nch/8);gr++) {
		if (Event->GrPresent[gr]) {
			for(ch=0; ch<9; ch++) {
				int Size = Event->DataGroup[gr].ChSize[ch];
				if (Size <= 0) {
					continue;
				}

				// Check the file format type
				if( WDcfg->OutFileFlags& OFF_BINARY) {
					// Binary file format
					uint32_t BinHeader[6];
					BinHeader[0] = (WDcfg->Nbit == 8) ? Size + 6*sizeof(*BinHeader) : Size*4 + 6*sizeof(*BinHeader);
					BinHeader[1] = EventInfo->BoardId;
					BinHeader[2] = EventInfo->Pattern;
					BinHeader[3] = ch;
					BinHeader[4] = EventInfo->EventCounter;
					BinHeader[5] = EventInfo->TriggerTimeTag;
					if (!WDrun->fout[(gr*9+ch)]) {
						char fname[100];
						if ((gr*9+ch) == 8) {
							sprintf(fname, "TR_%d_0.dat", gr);
							sprintf(trname,"TR_%d_0",gr);
							flag =1;
							}
							else if ((gr*9+ch) == 17) {
								sprintf(fname, "TR_0_%d.dat", gr);
								sprintf(trname,"TR_0_%d",gr);
								flag =1;
								}
								else if ((gr*9+ch) == 26) {
									sprintf(fname, "TR_0_%d.dat", gr);
									sprintf(trname,"TR_0_%d",gr);
									flag =1;
									}
									else if ((gr*9+ch) == 35) {
										sprintf(fname, "TR_1_%d.dat", gr);
										sprintf(trname,"TR_1_%d",gr);
										flag =1;
										}
										else 	{
											sprintf(fname, "wave_%d.dat", (gr*8)+ch);
											flag =0;
										}
						if ((WDrun->fout[(gr*9+ch)] = fopen(fname, "wb")) == NULL)
							return -1;
					}
					if( WDcfg->OutFileFlags & OFF_HEADER) {
						// Write the Channel Header
						if(fwrite(BinHeader, sizeof(*BinHeader), 6, WDrun->fout[(gr*9+ch)]) != 6) {
							// error writing to file
							fclose(WDrun->fout[(gr*9+ch)]);
							WDrun->fout[(gr*9+ch)]= NULL;
							return -1;
						}
					}
					ns = (int)fwrite( Event->DataGroup[gr].DataChannel[ch] , 1 , Size*4, WDrun->fout[(gr*9+ch)]) / 4;
					if (ns != Size) {
						// error writing to file
						fclose(WDrun->fout[(gr*9+ch)]);
						WDrun->fout[(gr*9+ch)]= NULL;
						return -1;
					}
				} else {
					// Ascii file format
					if (!WDrun->fout[(gr*9+ch)]) {
						char fname[100];
						if ((gr*9+ch) == 8) {
							sprintf(fname, "TR_%d_0.txt", gr);
							sprintf(trname,"TR_%d_0",gr);
							flag =1;
							}
							else if ((gr*9+ch) == 17) {
								sprintf(fname, "TR_0_%d.txt", gr);
								sprintf(trname,"TR_0_%d",gr);
								flag =1;
								}
								else if ((gr*9+ch) == 26) {
									sprintf(fname, "TR_0_%d.txt", gr);
									sprintf(trname,"TR_0_%d",gr);
									flag =1;
									}
									else if ((gr*9+ch) == 35) {
										sprintf(fname, "TR_1_%d.txt", gr);
										sprintf(trname,"TR_1_%d",gr);
										flag =1;
										}
										else 	{
											sprintf(fname, "wave_%d.txt", (gr*8)+ch);
											flag =0;
										}
						if ((WDrun->fout[(gr*9+ch)] = fopen(fname, "w")) == NULL)
							return -1;
					}
					if( WDcfg->OutFileFlags & OFF_HEADER) {
						// Write the Channel Header
						fprintf(WDrun->fout[(gr*9+ch)], "Record Length: %d\n", Size);
						fprintf(WDrun->fout[(gr*9+ch)], "BoardID: %2d\n", EventInfo->BoardId);
						if (flag)
						fprintf(WDrun->fout[(gr*9+ch)], "Channel: %s\n",  trname);
						else
						fprintf(WDrun->fout[(gr*9+ch)], "Channel: %d\n",  (gr*8)+ ch);
						fprintf(WDrun->fout[(gr*9+ch)], "Event Number: %d\n", EventInfo->EventCounter);
						fprintf(WDrun->fout[(gr*9+ch)], "Pattern: 0x%04X\n", EventInfo->Pattern & 0xFFFF);
						fprintf(WDrun->fout[(gr*9+ch)], "Trigger Time Stamp: %u\n", Event->DataGroup[gr].TriggerTimeTag);
						fprintf(WDrun->fout[(gr*9+ch)], "DC offset (DAC): 0x%04X\n", WDcfg->DCoffset[ch] & 0xFFFF);
						fprintf(WDrun->fout[(gr*9+ch)], "Start Index Cell: %d\n", Event->DataGroup[gr].StartIndexCell);
						flag = 0;
					}
					for(j=0; j<Size; j++) {
						fprintf(WDrun->fout[(gr*9+ch)], "%f\n", Event->DataGroup[gr].DataChannel[ch][j]);
					}
				}
				if (WDrun->SingleWrite) {
					fclose(WDrun->fout[(gr*9+ch)]);
					WDrun->fout[(gr*9+ch)]= NULL;
				}
			}
		}
	}
    return 0;

}

/* ########################################################################### */
/* MAIN                                                                        */
/* ########################################################################### */
int main(int argc, char *argv[])
{
	WaveDumpConfig_t   WDcfg;
    WaveDumpRun_t      WDrun;
    CAEN_DGTZ_ErrorCode ret=0;
    int  handle;
    ERROR_CODES ErrCode= ERR_NONE;
    int i, ch, Nb=0, Ne=0;
    uint32_t AllocatedSize, BufferSize, NumEvents;
    char *buffer = NULL;
    char *EventPtr = NULL;
    char ConfigFileName[100];
    int isVMEDevice= 0, MajorNumber;
    uint64_t CurrentTime, PrevRateTime, ElapsedTime;
    int nCycles= 0;
    CAEN_DGTZ_BoardInfo_t       BoardInfo;
    CAEN_DGTZ_EventInfo_t       EventInfo;
    
    CAEN_DGTZ_UINT16_EVENT_t    *Event16=NULL; /* generic event struct with 16 bit data (10, 12, 14 and 16 bit digitizers */
	
    CAEN_DGTZ_UINT8_EVENT_t     *Event8=NULL; /* generic event struct with 8 bit data (only for 8 bit digitizers) */ 
    CAEN_DGTZ_X742_EVENT_t       *Event742=NULL;  /* custom event struct with 8 bit data (only for 8 bit digitizers) */
    WDPlot_t                    *PlotVar=NULL;
    FILE *f_ini;
	DataCorrection_t Table_gr0, Table_gr1;

    printf("\n");
    printf("**************************************************************\n");
    printf("                        Wave Dump %s\n", WaveDump_Release);
    printf("**************************************************************\n");

    /* *************************************************************************************** */
    /* Open and parse configuration file                                                       */
    /* *************************************************************************************** */
    memset(&WDrun, 0, sizeof(WDrun));
    if (argc > 1)
        strcpy(ConfigFileName, argv[1]);
    else
        strcpy(ConfigFileName, DEFAULT_CONFIG_FILE);
    printf("Opening Configuration File %s\n", ConfigFileName);
    f_ini = fopen(ConfigFileName, "r");
    if (f_ini == NULL ) {
        ErrCode = ERR_CONF_FILE_NOT_FOUND;
        goto QuitProgram;
    }
    ParseConfigFile(f_ini, &WDcfg);
    fclose(f_ini);

    /* *************************************************************************************** */
    /* Open the digitizer and read the board information                                       */
    /* *************************************************************************************** */
    isVMEDevice = WDcfg.BaseAddress ? 1 : 0;

    /* HACK, the function to load the correction table is a CAENComm function, so we first open the
    device with CAENComm lib, read the the correction table and suddenly close the device. */
    if(WDcfg.useCorrections != -1) { // use Corrections Manually
        if (ret = CAENComm_OpenDevice((CAENComm_ConnectionType)WDcfg.LinkType,WDcfg.LinkNum,WDcfg.ConetNode,WDcfg.BaseAddress,&handle)) {
            ErrCode = ERR_DGZ_OPEN;
            goto QuitProgram;
        }
        
        if (ret = LoadCorrectionTables(handle, &Table_gr0, 0, CAEN_DGTZ_DRS4_5GHz))
            goto QuitProgram;

        if (ret = LoadCorrectionTables(handle, &Table_gr1, 1, CAEN_DGTZ_DRS4_5GHz))
            goto QuitProgram;

        if (ret = CAENComm_CloseDevice(handle))
            goto QuitProgram;

        SaveCorrectionTable("table0", Table_gr0);
        SaveCorrectionTable("table1", Table_gr1);
        // write tables to file
    }

    ret = CAEN_DGTZ_OpenDigitizer(WDcfg.LinkType, WDcfg.LinkNum, WDcfg.ConetNode, WDcfg.BaseAddress, &handle);
    if (ret) {
        ErrCode = ERR_DGZ_OPEN;
        goto QuitProgram;
    }

	if( WDcfg.useCorrections == -1 ) { // use automatic corrections
        ret = CAEN_DGTZ_LoadDRS4CorrectionData(handle,CAEN_DGTZ_DRS4_5GHz);
        ret = CAEN_DGTZ_EnableDRS4Correction(handle);
    }
    ret = CAEN_DGTZ_GetInfo(handle, &BoardInfo);
    if (ret) {
        ErrCode = ERR_BOARD_INFO_READ;
        goto QuitProgram;
    }
    printf("Connected to CAEN Digitizer Model %s\n", BoardInfo.ModelName);
    printf("ROC FPGA Release is %s\n", BoardInfo.ROC_FirmwareRel);
    printf("AMC FPGA Release is %s\n", BoardInfo.AMC_FirmwareRel);

    // Check firmware rivision (DPP firmwares cannot be used with WaveDump */
    sscanf(BoardInfo.AMC_FirmwareRel, "%d", &MajorNumber);
    if (MajorNumber >= 128) {
        printf("This digitizer has a DPP firmware\n");
        ErrCode = ERR_INVALID_BOARD_TYPE;
        goto QuitProgram;
    }

    // get num of channels, num of bit, num of group of the board */
    ret = GetMoreBoardInfo(handle,BoardInfo, &WDcfg);
    if (ret) {
        ErrCode = ERR_INVALID_BOARD_TYPE;
        goto QuitProgram;
    }
Restart:
    // mask the channels not available for this model
    if ((BoardInfo.FamilyCode != CAEN_DGTZ_XX740_FAMILY_CODE) && (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE)){
        WDcfg.EnableMask &= (1<<WDcfg.Nch)-1;
    } else {
        WDcfg.EnableMask &= (1<<(WDcfg.Nch/8))-1;
    }
    if ((BoardInfo.FamilyCode == CAEN_DGTZ_XX751_FAMILY_CODE) && WDcfg.DesMode) {
        WDcfg.EnableMask &= 0xAA;
    }
    if ((BoardInfo.FamilyCode == CAEN_DGTZ_XX731_FAMILY_CODE) && WDcfg.DesMode) {
        WDcfg.EnableMask &= 0x55;
    }
    // Set plot mask
    if ((BoardInfo.FamilyCode != CAEN_DGTZ_XX740_FAMILY_CODE) && (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE)){
        WDrun.ChannelPlotMask = WDcfg.EnableMask;
    } else {
        WDrun.ChannelPlotMask = (WDcfg.FastTriggerEnabled == 0) ? 0xFF: 0x1FF;
    }

    /* *************************************************************************************** */
    /* program the digitizer                                                                   */
    /* *************************************************************************************** */
    ret = ProgramDigitizer(handle, WDcfg, BoardInfo);
    if (ret) {
        ErrCode = ERR_DGZ_PROGRAM;
        goto QuitProgram;
    }

    // Allocate memory for the event data and readout buffer
    if(WDcfg.Nbit == 8)
        ret = CAEN_DGTZ_AllocateEvent(handle, (void**)&Event8);
    else {
		if (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE) {
			ret = CAEN_DGTZ_AllocateEvent(handle, (void**)&Event16);
		}
		else {
			ret = CAEN_DGTZ_AllocateEvent(handle, (void**)&Event742);
		}
    }
    if (ret != CAEN_DGTZ_Success) {
        ErrCode = ERR_MALLOC;
        goto QuitProgram;
    }
    ret = CAEN_DGTZ_MallocReadoutBuffer(handle, &buffer,&AllocatedSize); /* WARNING: This malloc must be done after the digitizer programming */
    if (ret) {
        ErrCode = ERR_MALLOC;
        goto QuitProgram;
    }

	//if (WDcfg.TestPattern) CAEN_DGTZ_DisableDRS4Correction(handle);
	//else CAEN_DGTZ_EnableDRS4Correction(handle);

    if (WDrun.Restart && WDrun.AcqRun)
        CAEN_DGTZ_SWStartAcquisition(handle);
    else
        printf("[s] start/stop the acquisition, [q] quit, [SPACE] help\n");
    WDrun.Restart = 0;
    PrevRateTime = get_time();
    /* *************************************************************************************** */
    /* Readout Loop                                                                            */
    /* *************************************************************************************** */
    while(!WDrun.Quit) {

        // Check for keyboard commands (key pressed)
        CheckKeyboardCommands(handle, &WDrun, &WDcfg, BoardInfo);
        if (WDrun.Restart) {
            CAEN_DGTZ_SWStopAcquisition(handle);
            CAEN_DGTZ_FreeReadoutBuffer(&buffer);
            ClosePlotter();
            PlotVar = NULL;
            if(WDcfg.Nbit == 8)
                CAEN_DGTZ_FreeEvent(handle, (void**)&Event8);
            else
				if (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE) {
					CAEN_DGTZ_FreeEvent(handle, (void**)&Event16);
				}
				else {
				    CAEN_DGTZ_FreeEvent(handle, (void**)&Event742);
				}
            f_ini = fopen(ConfigFileName, "r");
            ParseConfigFile(f_ini, &WDcfg);
            fclose(f_ini);
            goto Restart;
        }
        if (WDrun.AcqRun == 0)
            continue;

        /* Send a software trigger */
        if (WDrun.ContinuousTrigger) {
            CAEN_DGTZ_SendSWtrigger(handle);
        }

        /* Wait for interrupt (if enabled) */
        if (WDcfg.InterruptNumEvents > 0) {
            int32_t boardId;
            int VMEHandle;
            int InterruptMask = (1 << VME_INTERRUPT_LEVEL);

            BufferSize = 0;
            NumEvents = 0;
            // Interrupt handling
            if (isVMEDevice)
                ret = CAEN_DGTZ_VMEIRQWait (WDcfg.LinkType, WDcfg.LinkNum, WDcfg.ConetNode, InterruptMask, INTERRUPT_TIMEOUT, &VMEHandle);
            else
                ret = CAEN_DGTZ_IRQWait(handle, INTERRUPT_TIMEOUT);
            if (ret == CAEN_DGTZ_Timeout)  // No active interrupt requests
                goto InterruptTimeout;
            if (ret != CAEN_DGTZ_Success)  {
                ErrCode = ERR_INTERRUPT;
                goto QuitProgram;
            }
            // Interrupt Ack
            if (isVMEDevice) {
                ret = CAEN_DGTZ_VMEIACKCycle(VMEHandle, VME_INTERRUPT_LEVEL, &boardId);
                if ((ret != CAEN_DGTZ_Success) || (boardId != VME_INTERRUPT_STATUS_ID)) {
                    goto InterruptTimeout;
                } else {
                    if (INTERRUPT_MODE == CAEN_DGTZ_IRQ_MODE_ROAK)
                        ret = CAEN_DGTZ_RearmInterrupt(handle);
				}
			}
        }

        /* Read data from the board */
        ret = CAEN_DGTZ_ReadData(handle, CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT, buffer, &BufferSize);
        if (ret) {

            ErrCode = ERR_READOUT;
            goto QuitProgram;
        }
        NumEvents = 0;
        if (BufferSize != 0) {
            ret = CAEN_DGTZ_GetNumEvents(handle, buffer, BufferSize, &NumEvents);
            if (ret) {
                ErrCode = ERR_READOUT;
                goto QuitProgram;
            }
        }
InterruptTimeout:
        /* Calculate throughput and trigger rate (every second) */
        Nb += BufferSize;
        Ne += NumEvents;
        CurrentTime = get_time();
        ElapsedTime = CurrentTime - PrevRateTime;

        nCycles++;
        if (ElapsedTime > 1000) {
            if (Nb == 0)
                if (ret == CAEN_DGTZ_Timeout) printf ("Timeout...\n"); else printf("No data...\n");
            else
                printf("Reading at %.2f MB/s (Trg Rate: %.2f Hz)\n", (float)Nb/((float)ElapsedTime*1048.576f), (float)Ne*1000.0f/(float)ElapsedTime);
            nCycles= 0;
            Nb = 0;
            Ne = 0;
            PrevRateTime = CurrentTime;
        }

        /* Analyze data */
        for(i = 0; i < (int)NumEvents; i++) {

            /* Get one event from the readout buffer */
            ret = CAEN_DGTZ_GetEventInfo(handle, buffer, BufferSize, i, &EventInfo, &EventPtr);
            if (ret) {
                ErrCode = ERR_EVENT_BUILD;
                goto QuitProgram;
            }
            /* decode the event */
            if (WDcfg.Nbit == 8) 
                ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event8);
            else
                if (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE) {
					ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event16);
				}
				else {
					ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event742);
                    if(WDcfg.useCorrections != -1) { // if manual corrections
					    ApplyDataCorrection( 0, WDcfg.useCorrections, CAEN_DGTZ_DRS4_5GHz, &(Event742->DataGroup[0]), &Table_gr0);
					    ApplyDataCorrection( 1, WDcfg.useCorrections, CAEN_DGTZ_DRS4_5GHz, &(Event742->DataGroup[1]), &Table_gr1);
                    }
				}
            if (ret) {
                ErrCode = ERR_EVENT_BUILD;
                goto QuitProgram;
            }

            /* Update Histograms */
            if (WDrun.RunHisto) {
                for(ch=0; ch<WDcfg.Nch; ch++) {
                    int chmask = ((BoardInfo.FamilyCode == CAEN_DGTZ_XX740_FAMILY_CODE) || (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) )? (ch/8) : ch;
                    if (!(EventInfo.ChannelMask & (1<<chmask)))
                        continue;
                    if (WDrun.Histogram[ch] == NULL) {
                        if ((WDrun.Histogram[ch] = malloc((1<<WDcfg.Nbit) * sizeof(uint32_t))) == NULL) {
                            ErrCode = ERR_HISTO_MALLOC;
                            goto QuitProgram;
                        }
                        memset(WDrun.Histogram[ch], 0, (1<<WDcfg.Nbit) * sizeof(uint32_t));
                    }
                    if (WDcfg.Nbit == 8)
                        for(i=0; i<(int)Event8->ChSize[ch]; i++)
                            WDrun.Histogram[ch][Event8->DataChannel[ch][i]]++;
                    else
                        for(i=0; i<(int)Event16->ChSize[ch]; i++)
                            WDrun.Histogram[ch][Event16->DataChannel[ch][i]]++;
                }
            }

			/* Write Event data to file */
			if (WDrun.ContinuousWrite || WDrun.SingleWrite) {
				// Note: use a thread here to allow parallel readout and file writing
				if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) {	
					ret = WriteOutputFilesx742(&WDcfg, &WDrun, &EventInfo, Event742); 
				}
				else if (WDcfg.Nbit == 8) {
					ret = WriteOutputFiles(&WDcfg, &WDrun, &EventInfo, Event8);
				}
				else {
					ret = WriteOutputFiles(&WDcfg, &WDrun, &EventInfo, Event16);
				}
				if (ret) {
					ErrCode = ERR_OUTFILE_WRITE;
					goto QuitProgram;
				}
				if (WDrun.SingleWrite) {
					printf("Single Event saved to output files\n");
					WDrun.SingleWrite = 0;
				}
			}

            /* Plot Waveforms */
            if ((WDrun.ContinuousPlot || WDrun.SinglePlot) && !IsPlotterBusy()) {
                int Ntraces = (BoardInfo.FamilyCode == CAEN_DGTZ_XX740_FAMILY_CODE) ? 8 : WDcfg.Nch;
                if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) Ntraces = 9;
                if (PlotVar == NULL) {
                    int TraceLength = max(WDcfg.RecordLength, (1<<WDcfg.Nbit));
                    PlotVar = OpenPlotter(WDcfg.GnuPlotPath, Ntraces, TraceLength);
                    WDrun.SetPlotOptions = 1;
                }
                if (PlotVar == NULL) {
                    printf("Can't open the plotter\n");
                    WDrun.ContinuousPlot = 0;
                    WDrun.SinglePlot = 0;
                } else {
                    int Tn = 0;
                    if (WDrun.SetPlotOptions) {
						if ((WDrun.PlotType == PLOT_WAVEFORMS) && (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE)) {
                            PlotVar->Xscale = WDcfg.Ts;
                            strcpy(PlotVar->Xlabel, "ns");
                            strcpy(PlotVar->Ylabel, "ADC counts");
                            PlotVar->Yautoscale = 0;
                            PlotVar->Ymin = 0;
                            PlotVar->Ymax = (float)(1<<WDcfg.Nbit);
                            PlotVar->Xautoscale = 1;
                        } else if (WDrun.PlotType == PLOT_WAVEFORMS) {
                            PlotVar->Xscale = WDcfg.Ts/1000;
                            strcpy(PlotVar->Xlabel, "us");
                            strcpy(PlotVar->Ylabel, "ADC counts");
                            PlotVar->Yautoscale = 0;
                            PlotVar->Ymin = 0;
                            PlotVar->Ymax = (float)(1<<WDcfg.Nbit);
                            PlotVar->Xautoscale = 1;
                        }  else if (WDrun.PlotType == PLOT_FFT) {
                            strcpy(PlotVar->Xlabel, "MHz");
                            strcpy(PlotVar->Ylabel, "dB");
                            PlotVar->Yautoscale = 1;
                            PlotVar->Ymin = -160;
                            PlotVar->Ymax = 0;
                            PlotVar->Xautoscale = 1;
                        } else if (WDrun.PlotType == PLOT_HISTOGRAM) {
                            PlotVar->Xscale = 1.0;
                            strcpy(PlotVar->Xlabel, "ADC channels");
                            strcpy(PlotVar->Ylabel, "Counts");
                            PlotVar->Yautoscale = 1;
                            PlotVar->Xautoscale = 1;
                        }
                        SetPlotOptions();
                        WDrun.SetPlotOptions = 0;
                    }
                    for(ch=0; ch<Ntraces; ch++) {
                        int absCh = WDrun.GroupPlotIndex*8+ch;

                        if (!((WDrun.ChannelPlotMask >> ch) & 1))
                            continue;
                       if ((BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) && ((ch != 0) && (absCh % 8) == 0)) sprintf(PlotVar->TraceName[Tn], "TR %d", (int)((absCh-1) / 16));
                       else sprintf(PlotVar->TraceName[Tn], "CH %d", absCh);
                        if (WDrun.PlotType == PLOT_WAVEFORMS) {
                            strcpy(PlotVar->Title, "Waveform");
                            if (WDcfg.Nbit == 8) {
                                PlotVar->TraceSize[Tn] = Event8->ChSize[absCh];
                                memcpy(PlotVar->TraceData[Tn], Event8->DataChannel[absCh], Event8->ChSize[absCh]);
                                PlotVar->DataType = PLOT_DATA_UINT8;
							} else if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) {
								if (Event742->GrPresent[WDrun.GroupPlotIndex]) { 
									PlotVar->TraceSize[Tn] = Event742->DataGroup[WDrun.GroupPlotIndex].ChSize[ch];
									memcpy(PlotVar->TraceData[Tn], Event742->DataGroup[WDrun.GroupPlotIndex].DataChannel[ch], Event742->DataGroup[WDrun.GroupPlotIndex].ChSize[ch] * sizeof(float));
									PlotVar->DataType = PLOT_DATA_FLOAT;
									}
								}
                            else {
								PlotVar->TraceSize[Tn] = Event16->ChSize[absCh];
                                memcpy(PlotVar->TraceData[Tn], Event16->DataChannel[absCh], Event16->ChSize[absCh] * 2);
                                PlotVar->DataType = PLOT_DATA_UINT16;
                           }  
                        } else if (WDrun.PlotType == PLOT_FFT) {
                            int FFTns;
                            strcpy(PlotVar->Title, "FFT");
                            PlotVar->DataType = PLOT_DATA_DOUBLE;
                            FFTns = FFT(Event16->DataChannel[absCh], PlotVar->TraceData[Tn], Event16->ChSize[absCh], HANNING_FFT_WINDOW);
                            PlotVar->Xscale = (1000/WDcfg.Ts)/(2*FFTns);
                            PlotVar->TraceSize[Tn] = FFTns;
                        } else if (WDrun.PlotType == PLOT_HISTOGRAM) {
                            PlotVar->DataType = PLOT_DATA_UINT32;
                            strcpy(PlotVar->Title, "Histogram");
                            PlotVar->TraceSize[Tn] = 1<<WDcfg.Nbit;
                            memcpy(PlotVar->TraceData[Tn], WDrun.Histogram[absCh], (1<<WDcfg.Nbit) * sizeof(uint32_t));
                        }
                        Tn++;
                        if (Tn >= MAX_NUM_TRACES)
                            break;
                    }
                    PlotVar->NumTraces = Tn;
                    if( PlotWaveforms() < 0) {
                        WDrun.ContinuousPlot = 0;
                        printf("Plot Error\n");
                    }
                    WDrun.SinglePlot = 0;
                }
            }
        }
    }
    ErrCode = ERR_NONE;

QuitProgram:
    if (ErrCode) {
        printf("\a%s\n", ErrMsg[ErrCode]);
#ifdef WIN32
        printf("Press a key to quit\n");
		getch();
#endif
    }

    /* stop the acquisition */
    CAEN_DGTZ_SWStopAcquisition(handle);

    /* close the plotter */
    if (PlotVar)
        ClosePlotter();

    /* close the output files and free histograms*/
    for(ch=0; ch<WDcfg.Nch; ch++) {
        if( WDrun.fout[ch])
            fclose(WDrun.fout[ch]);
        if( WDrun.Histogram[ch])
            free(WDrun.Histogram[ch]);
    }

    /* close the device and free the buffers */
    if(Event8)
        CAEN_DGTZ_FreeEvent(handle, (void**)&Event8);
    if(Event16)
        CAEN_DGTZ_FreeEvent(handle, (void**)&Event16);
    CAEN_DGTZ_FreeReadoutBuffer(&buffer);
    CAEN_DGTZ_CloseDigitizer(handle);

    return 0;
}
