/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** core_loop
*/

// # game loop (launch)

// ### - get current instruction of each process
// - if instruction byte is not valid, set cmd to NULL WILL BE VERIFIED
// - set countdown to the corresponding intruction

// ### - execute the instruction
// - if the instruction is NULL (kill the process | set do dead)
// - otherwise if the countdown is 0 **execute the instruction**
// - else do nothing ((skip))

// ### - cleanup
// - check if a process is dead () -> free
// - check if a player is dead (process count == 0) -> free
// - if there is only one player left setwin
// - if nbr_live is >= crr_live decrease curr_period by cycle_delta

// ### - Dump
// - if flag print status

#include "vm.h"
#include "cbuffer.h"
#include "serrorh.h"
#include "instructions.h"
#include "mystr.h"

static int core_end(vm_t *vm)
{
    if (vm->champions->size == 0) {
        my_putstr("No winner\n");
        return (1);
    }
    if (vm->champions->size == 1) {
        my_fputstr(1, "The player ");
        my_fputnbr(1, ((champion_t *)vm->champions->head)->id);
        my_fputstr(1, "(");
        my_fputstr(1, ((champion_t *)vm->champions->head)->header.prog_name);
        my_fputstr(1, ")has won.\n");
        return (1);
    }
    return (0);
}

static void kill_champion_processes(vm_t *vm, champion_t *champion)
{
    node_t *node = vm->process->head;
    process_t *process = NULL;
    process_t *temp = NULL;

    while (node != NULL) {
        process = node->data;
        if (process->champion == champion) {
            kill_process(process, vm);
        }
        node = node->next;
    }
}

static void champion_reset_live(any_t data, void *vm_ptr)
{
    champion_t *champion = data;
    vm_t *vm = vm_ptr;

    if (champion->alive == false) {
        my_fprintf(1, "The player %d(%s) has been killed by the game.\n",
        champion->id, champion->header.prog_name);
        kill_champion_processes(vm, champion);
    }
    champion->alive = false;
}

static int core_check(vm_t *vm)
{
    vm->cycle_amount++;
    vm->total_cycle++;
    if (vm->cycle_amount >= vm->cycle_to_die) {
        vm->cycle_amount = 0;
        vm->curr_period++;
        if (vm->has_dump && vm->total_cycle >= vm->dump_cycle) {
            print_string_byte_per_byte(vm->arena, vm->arena->size);
            return 1;
        }
        if (vm->local_live >= NBR_LIVE) {
            vm->cycle_to_die -= CYCLE_DELTA;
            vm->local_live = 0;
            list_foreach(vm->champions, &champion_reset_live);

        }
    }
    return 0;
}

void core_loop(vm_t *vm)
{
    while (vm->cycle_to_die > 0) {
        instruction_get(vm);
        instruction_exec(vm);
        if (core_check(vm))
            return;
        if (core_end(vm))
            return;
    }
}
