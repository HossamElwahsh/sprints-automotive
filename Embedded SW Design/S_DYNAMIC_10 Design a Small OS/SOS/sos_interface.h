/**
 * @file    :   sos_interface.h
 * @author  :   Hossam Elwahsh - https://github.com/HossamElwahsh
 * @brief   :   Header File contains all the types and status code for SOS
 * @version :   1.0
 * @date    :   2023-05-29
 *
 * @copyright Copyright (c) 2023
 */ 


#ifndef SOS_INTERFACE_H_
#define SOS_INTERFACE_H_

#include "sos_preconfig.h"
#include "../std.h"

/* --------------------- ENUMS --------------------- */

typedef enum
{
    SOS_STATUS_SUCCESS          =   0       ,
    SOS_STATUS_FAILED                       ,
    SOS_STATUS_INVALID_STATE                ,
    SOS_STATUS_INVALID_INVALID_TASK_ID      ,
    SOS_STATUS_TOTAL
}enu_system_status_t_;

typedef enum
{
    /** SOS is yet to be initialized */
    SOS_STATE_UNINITIALIZED =   0   ,

    /** SOS initialized and ready to run */
    SOS_STATE_READY                 ,

    /** SOS is running */
    SOS_STATE_RUNNING               ,

    /** SOS is idle */
    SOS_STATE_IDLE                  ,

    /** SOS is stopped */
    SOS_STATE_STOPPED               ,

    SOS_STATE_TOTAL
}enu_sos_state_t_;

/* --------------------- STRUCTS --------------------- */

typedef struct
{
    void        (* ptr_fun_task)(void)      ;
    uint16_t_   uint16_task_unique_id       ;
    uint16_t_   uint16_task_priority        ;
    uint16_t_   uint16_task_interval        ;
    uint16_t_   uint16_task_delay           ;
}str_sos_task_t_;

typedef struct
{
    uint16_t_           uint16_active_tasks             ;
    str_sos_task_t_     str_sos_tasks[SOS_MAX_TASKS]    ;
}str_sos_database_t_;

/* --------------------- Functions' Prototypes --------------------- */

/**
 * @brief                               :   Initializes SOS
 *
 * @return  SOS_STATUS_SUCCESS          :   In case of Successful Operation
 *          SOS_STATUS_INVALID_STATE    :   In case the sos is already initialized
 */
enu_system_status_t_    sos_init            (void);

/**
 * @brief                               :   De-initializes SOS
 *
 * @return  SOS_STATUS_SUCCESS          :   In case of Successful Operation
 *          SOS_STATUS_INVALID_STATE    :   In case the sos is already de-initialized or was not initialized previously
 */
enu_system_status_t_    sos_deinit          (void);

/**
 * @brief                               :   Creates a new task
 *
 * @param ptr_str_sos_task              :   Pointer to task to be created
 *
 * SOS_STATUS_SUCCESS                   :   In case of Successful Operation (created)
 * SOS_STATUS_FAILED                    :   In case of Failed Operation (scheduler full / not init)
 */
enu_system_status_t_    sos_create_task     (str_sos_task_t_ * ptr_str_sos_task);

/**
 * @brief                               :   Deletes a task by it's ID
 *
 * @param uint16_task_unique_id         :   Task ID for the task to be deleted
 *
 * SOS_STATUS_SUCCESS                   :   In case of Successful Operation (deleted)
 * SOS_STATUS_FAILED                    :   In case of Failed Operation (failed to delete)
 * SOS_STATUS_INVALID_INVALID_TASK_ID   :   In case of Failed Operation (ID doesn't exist)
 */
enu_system_status_t_    sos_delete_task     (uint16_t_ uint16_task_unique_id);

/**
 * @brief                               :   Modifies an existing task by it's ID
 *
 * @param ptr_str_sos_task              :   Pointer to new task values including the task ID to be modified
 *
 * SOS_STATUS_SUCCESS                   :   In case of Successful Operation (modified)
 * SOS_STATUS_FAILED                    :   In case of Failed Operation (failed to modify)
 * SOS_STATUS_INVALID_INVALID_TASK_ID   :   In case of Failed Operation (ID doesn't exist)
 */
enu_system_status_t_    sos_modify_task     (str_sos_task_t_ * ptr_str_sos_task);

/**
 * @brief                               :   Runs/Starts the scheduler
 * @return  SOS_STATUS_SUCCESS          :   In case of Successful Operation (started)
 *          SOS_STATUS_FAILED           :   In case of failing to start the scheduler
 *          SOS_STATUS_INVALID_STATE    :   In case Failed Operation; (SOS is already running, not init, was de-init)
 */
enu_system_status_t_    sos_run             (void);


/**
 * @brief                               :   Stops the scheduler
 *
 * @return  SOS_STATUS_SUCCESS          :   In case of Successful Operation
 *          SOS_STATUS_INVALID_STATE    :   In case of Failed Operation; (SOS is not running, not init, not de-init)
 */
enu_system_status_t_    sos_disable         (void);


/**
 * @brief event called when selected timer ticks (callback)
 *
 */
void sos_tick_event                         (void);


#endif /* SOS_INTERFACE_H_ */