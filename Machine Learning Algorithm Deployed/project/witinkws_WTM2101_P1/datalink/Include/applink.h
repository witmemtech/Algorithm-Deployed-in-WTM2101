/* vim: set fileencoding=utf-8:
 *
 *                   GNU GENERAL PUBLIC LICENSE
 *                       Version 2, June 1991
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 *
 */
#ifndef APPLINK_H_778E970A_1223_05DF_FDAA_48A8659ED4C2_INCLUDED_
#define APPLINK_H_778E970A_1223_05DF_FDAA_48A8659ED4C2_INCLUDED_

////////////////////////////////////////////////////////////////////////////////
//
//  sender          receiver
//      |    (BEGIN)    |
//      |               |
//      |----> info --->|
//      |<---- ack <----|
//      |               |
//      |----> data --->|
//      |<---- ack <----|
//      |               |
//      |----> data --->|
//      |<---- ack <----|
//
//           (......)
//
//      |----> data --->|
//      |<---- ack <----|
//      |               |
//      |----> crc ---->|
//      |     (END)     |
//
//
#define BYTES_PER_DATA_PKG  (160*sizeof(int16_t))

#define HEARTBEAT_TMO        500 // 0.5 second
#define ALIVE_TMO           5000 // 5 seconds
#define ACK_TMO             1000 // 1 seconds
#define DATA_RETRIES		   5 // resend data when missing ack
#define BUSY_TMO             500 // 0.5 second


typedef enum {
    APPLINK_ERROR   = 0,
    APPLINK_OK      = 1,
    APPLINK_BREAK   = 2,
}applink_result_t;


typedef void* applink_dev_t;
typedef struct applink_handle_t applink_handle_t;

//
//@retval >0    actual bytes sent
//@retval 0     nothing
//@retval -1    error
//
int user_send_msg(applink_dev_t dev, const uint8_t* data, int length);

//
//
//@retval >0    actual bytes received
//@retval 0     nothing
//@retval -1    error
//
int user_recv_msg(applink_dev_t dev, uint8_t* buffer, int maxsize);

int user_kbhit(void);

uint32_t user_get_tick(void);

void user_sleep(uint32_t ms);


// written by user
applink_result_t callback_link_connected(
	applink_handle_t* self,
	uint32_t version_date,
	uint32_t version_time);

applink_result_t callback_connection_lost(applink_handle_t* self);

applink_result_t callback_get_file_info(
        applink_handle_t*   self,
        void*               user,
        uint32_t            fileid,
        char                name[128],
        uint32_t*           pfileid,
        uint32_t*           plength);

applink_result_t callback_get_file_data(
        applink_handle_t*   self,
        void*               user,
        uint32_t            fileid,
        uint32_t            offset,
        uint32_t            length,
        uint8_t*            buffer);

applink_result_t callback_get_file_crc(
        applink_handle_t*   self,
        void*               user,
        uint32_t            fileid,
        uint32_t*           pcrcval);

applink_result_t callback_set_file_info(
        applink_handle_t*   self,
        void*               user,
        uint32_t            fileid,
        uint32_t            length);

applink_result_t callback_set_file_data(
        applink_handle_t*   self,
        void*               user,
        uint32_t            fileid,
        uint32_t            dataid,
        const void*         data,
        uint32_t            length);

applink_result_t callback_file_received(
        applink_handle_t*   self,
        void*               user,
        uint32_t            fileid);

applink_result_t callback_file_sent(
        applink_handle_t*   self,
        void*               user,
        uint32_t            fileid);

applink_result_t callback_debug_received(
        applink_handle_t*   self,
        void*               user,
        uint8_t*            buffer,
        uint32_t            length);



#endif

