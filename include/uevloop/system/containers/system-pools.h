/** \file system-pools.h
  * \brief A container for the system's internal pools
  */

#ifndef UEL_SYSTEM_POOLS_H
#define	UEL_SYSTEM_POOLS_H

#ifdef __cplusplus
extern "C" {
#endif

/// \cond
#include <stdint.h>
/// \endcond

#include "uevloop/config.h"
#include "uevloop/utils/linked-list.h"
#include "uevloop/utils/object-pool.h"
#include "uevloop/system/event.h"

/** \brief A container for the system pools
  *
  * The syspools object is meant as a container for the internal system pools.
  * It is a safe interface to the pools, acquiring and releasing objects on demand.
  */
typedef struct syspools uel_syspools_t;
struct syspools{

    //! Unrolls the `UEL_SYSPOOLS_EVENT_POOL_SIZE_LOG2N` value to its power-of-two form
    #define UEL_SYSPOOLS_EVENT_POOL_SIZE (1<<UEL_SYSPOOLS_EVENT_POOL_SIZE_LOG2N)
    //! The buffer used to store events in the event pool
    uel_event_t event_pool_buffer[UEL_SYSPOOLS_EVENT_POOL_SIZE];
    //! The buffer used to store event pointers in the event pool queue
    void *event_pool_queue_buffer[UEL_SYSPOOLS_EVENT_POOL_SIZE];
    //! The event pool object. Contains all the events used by the core.
    uel_objpool_t event_pool;

    //! Unrolls the `UEL_SYSPOOLS_LLIST_NODE_POOL_SIZE_LOG2N` value to its power-of-two form
    #define UEL_SYSPOOLS_LLIST_NODE_POOL_SIZE (1<<UEL_SYSPOOLS_LLIST_NODE_POOL_SIZE_LOG2N)
    //! The buffer used to store llist nodes in the llist node pool
    uel_llist_node_t llist_node_pool_buffer[UEL_SYSPOOLS_LLIST_NODE_POOL_SIZE];
    //! The budder used to store llist node pointers in the llist node pool queue
    void *llist_node_pool_queue_buffer[UEL_SYSPOOLS_LLIST_NODE_POOL_SIZE];
    //! The llist node pool object. Contains all llist nodes used by the core.
    uel_objpool_t llist_node_pool;
};

/** \brief Initialise the system pools
  *
  * \param pools The uel_syspools_t instance
  */
void uel_syspools_init(uel_syspools_t *pools);

/** \brief Acquires an event from the system pools
  *
  * \param pools The uel_syspools_t instance
  * \returns The acquired event
  */
uel_event_t *uel_syspools_acquire_event(uel_syspools_t *pools);

/** \brief Acquires a linked list node from the system pools
  *
  * \param pools The uel_syspools_t instance
  * \returns The acquired linked list node
  */
uel_llist_node_t *uel_syspools_acquire_llist_node(uel_syspools_t *pools);

/** \brief Releases an event to the system pools
  *
  * \param pools The uel_syspools_t instance
  * \param event The event to be released
  * \returns Whether the event was successfully released
  */
bool uel_syspools_release_event(uel_syspools_t *pools, uel_event_t *event);

/** \brief Releases a linked list node to the system pools
  *
  * \param pools The uel_syspools_t instance
  * \param node The linked list node to be released
  * \returns Wheter the linked list node was successfully released
  */
bool uel_syspools_release_llist_node(uel_syspools_t *pools, uel_llist_node_t *node);

#ifdef __cplusplus
}
#endif

#endif	/* UEL_SYSTEM_POOLS_H */
