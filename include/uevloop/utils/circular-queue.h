/** \file circular-queue.h
  *
  * \brief Defines circular queues, fast and efficient FIFO data structures
  */

#ifndef UEL_CIRCULAR_QUEUE_H
#define	UEL_CIRCULAR_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

/// \cond
#include <stdint.h>
#include <stdbool.h>
/// \endcond

/** \brief Defines a circular queue of void pointers
  *
  * The circular queue implementation provided is a fast and memory efficient
  * FIFO data structure that holds void pointers.
  *
  * Its capacity is **required** to be a power of two. This makes possible to
  * use fast modulo-2 arithmetic when dealing with the queue indices.
  */
typedef struct uel_cqueue uel_cqueue_t;
struct uel_cqueue {
    //! The buffer that will contain the enqueued values.
    void **buffer;
    //! The size of the queue. Must be a power of two.
    uintptr_t size;
    //! The mask used to wrap the indices around the capacity of the queue when
    //! they are incremented during pushs/pops
    uintptr_t mask;
    //! The position that indicates where the oldest enqueued element is
    uintptr_t tail;
    //! The count of enqueued elements.
    //! New elements are put at (tail + count) % size.
    uintptr_t count;
};

/** \brief Initialised a circular queue object
  *
  * \param queue The queue object to be intialised
  * \param buffer An array of void pointers that will be used to store the enqueued
  * values.
  * \param size_log2n The size of the queue in its log2 form.
  */
void uel_cqueue_init(uel_cqueue_t *queue, void **buffer, uintptr_t size_log2n);

/** \brief Empties a queue by resetting its tail and count values.
  *
  * \param queue The queue to be cleared.
  * \param clear_buffer If this is set, completely de-initialises the queue.
  */
void uel_cqueue_clear(uel_cqueue_t *queue, bool clear_buffer);

/** \brief Pushes an element into the queue
  *
  * \param queue The queue into which to push the element
  * \param element The element to be pushed into the queue
  * \return Whether the push operation was successfull
  */
bool uel_cqueue_push(uel_cqueue_t *queue, void *element);

/** \brief Pops an element from the queue.
  *
  * \param queue The queue from where to pop
  * \return The oldest element in the queue, if it exists. Otherwise, NULL.
  */
void *uel_cqueue_pop(uel_cqueue_t *queue);

/** \brief Peeks the tail of the queue, where the oldest element is enqueued.
  * This is the element that will be returned on the next pop operation.
  *
  * \param queue The queue to peek
  * \return The oldest element in the queue if it exists. Otherwise, NULL.
  */
void *uel_cqueue_peek_tail(uel_cqueue_t *queue);

/** \brief Peeks the head of the queue, where the newest element is enqueued.
* This is the element that was enqueued on the last push operation.
*
* \param queue The queue to peek
* \return The newest element in the queue if it exists. Otherwise, NULL.
*/
void *uel_cqueue_peek_head(uel_cqueue_t *queue);

/** \brief Checks if the queue is full
  *
  * \param queue The queue to check
  * \return Whether the queue is full or not
  */
bool uel_cqueue_is_full(uel_cqueue_t *queue);

/** \brief Checks if the queue is empty. Use this before popping from the queue.
*
* \param queue The queue to check
* \return Whether the queue is empty or not
*/
bool uel_cqueue_is_empty(uel_cqueue_t *queue);

/** \brief Counts the number o elements in the queue
  *
  * \param queue The queue whoese elements should be counted
  * \returns The number of enqueued elements
  */
uintptr_t uel_cqueue_count(uel_cqueue_t *queue);

#ifdef __cplusplus
}
#endif

#endif	/* UEL_CIRCULAR_QUEUE_H */
