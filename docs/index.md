# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`ALIGNMENT`](#alignment_8h_1a450f9d8af07bfe2f313dbe3a78738a5e)            | 
`define `[`class_alignment`](#containers_8h_1a260ce407668618187dc13842c095a647)            | 
`define `[`TASK_SCHEDULER_DISABLED`](#defines_8h_1ae9b1df2b104a6682d02254d8504aa3cb)            | 
`define `[`TASK_SCHEDULER_ENABLED`](#defines_8h_1a78dd1c60aa9944594bfdc56e78389a38)            | 
`define `[`TASK_SCHEDULER_PROFILER_NONE`](#defines_8h_1aafdb6b6d5c1d278e51de4dc7eab6ba5f)            | 
`define `[`TASK_SCHEDULER_PROFILER_ITT`](#defines_8h_1ae6c55a565b1fa61326e3b687971e7137)            | 
`define `[`task_scheduler_default_mem_interface_catch_all_allocations`](#memory_8h_1a7908572757e9ecd35e78b16de28f5b43)            | 
`define `[`optimization`](#meta_8h_1a9ff5da7d3d16a1bd047a76e2d68782f0)            | 
`define `[`reduce_starvation`](#meta_8h_1a4baf8b0d017cab46679be16a6a456eb2)            | 
`define `[`ts_windows_only`](#platform_8h_1a372ddc9444b8d67b78ca4390bc16eaf3)            | 
`define `[`tchar_t`](#platform_8h_1acf7a0908ceed3a6ad09958993aae6868)            | 
`define `[`_t`](#platform_8h_1aabc341906992e6fc99ffb879df3003c7)            | 
`define `[`ts_print_internal`](#print_8h_1a17099dcee86b45b08093146e333907a3)            | 
`define `[`ts_print`](#print_8h_1a52e7a19f22557adf8886357947f0b815)            | 
`define `[`ts_debug_only`](#utils_8h_1a569b826ad125451b8358c4a0385fb985)            | 
`define `[`ts_assert`](#utils_8h_1a025700f763a0dbb62173ab080884329a)            | 
`define `[`ts_always_assert`](#utils_8h_1a59627301966eb7bd49bf4860004823d9)            | 
`define `[`ts_itt`](#utils_8h_1a6bab8188114862bfcf8ad054c7135389)            | 
`define `[`ts_join_string`](#utils_8h_1ac9491a767789204698d1ee7b1f3ac863)            | 
`define `[`ts_do_join`](#utils_8h_1aaafd1202c51b64c616032d417fe64fd9)            | 
`define `[`ts_unique_variable`](#utils_8h_1ab33a568c06366a76235b9a5a01e6226e)            | 
`define `[`ts_unused`](#utils_8h_1a5755c9df6d339aa6eb1a303ac9ba6601)            | 
`define `[`ts_declare_attribute_and_callbacks`](#utils_8h_1a7c3470866bab76b82670a8bcf3b7f2e9)            | 
`define `[`ts_init_attribute_and_callbacks`](#utils_8h_1adc341c494347f788c80023428fc411de)            | 
`define `[`ts_declare_attribute`](#utils_8h_1a3b90c42ae60ecb4871d3bb47ebe7970a)            | 
`define `[`ts_init_attribute`](#utils_8h_1a42d958decfcd15195b2a488247dde6ee)            | 
`define `[`TASK_SCHEDULER_PROFILER`](#tests_2multi__threaded__detector_2main_8cpp_1a9ea10af1191c1eec7fde05db51f5aab4)            | 
`define `[`TASK_SCHEDULER_DEBUG`](#samples_2basic_2stdafx_8h_1ac413d9542a19405f74c6699450163a7b)            | 
`define `[`TASK_SCHEDULER_ASSERT`](#samples_2basic_2stdafx_8h_1abd956a528a775769f07ab5af25d83ef3)            | 
`define `[`TASK_SCHEDULER_PROFILER`](#samples_2basic_2stdafx_8h_1a9ea10af1191c1eec7fde05db51f5aab4)            | 
`define `[`TASK_SCHEDULER_DEBUG`](#samples_2profile_2stdafx_8h_1ac413d9542a19405f74c6699450163a7b)            | 
`define `[`TASK_SCHEDULER_ASSERT`](#samples_2profile_2stdafx_8h_1abd956a528a775769f07ab5af25d83ef3)            | 
`define `[`TASK_SCHEDULER_PROFILER`](#samples_2profile_2stdafx_8h_1a9ea10af1191c1eec7fde05db51f5aab4)            | 
`define `[`TASK_SCHEDULER_DEBUG`](#tests_2multi__threaded__detector_2stdafx_8h_1ac413d9542a19405f74c6699450163a7b)            | 
`define `[`TASK_SCHEDULER_ASSERT`](#tests_2multi__threaded__detector_2stdafx_8h_1abd956a528a775769f07ab5af25d83ef3)            | 
`public  `[`task_scheduler_default_mem_interface_catch_all_allocations`](#samples_2basic_2main_8cpp_1ade4ab2d33186fff4f511f0b6b946acca)`()`            | 
`public void `[`RandomTimeTask`](#samples_2basic_2main_8cpp_1a1965f00a1f57e9a7ac227a5278eefd3b)`(chrono::milliseconds minTaskTime,chrono::milliseconds maxTaskTime)`            | Randoms the time task.
`public int `[`main`](#samples_2basic_2main_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()`            | Mains this instance.
`public  `[`task_scheduler_default_mem_interface_catch_all_allocations`](#samples_2profile_2main_8cpp_1ade4ab2d33186fff4f511f0b6b946acca)`()`            | 
`public void `[`RandomTimeTask`](#samples_2profile_2main_8cpp_1a1965f00a1f57e9a7ac227a5278eefd3b)`(chrono::milliseconds minTaskTime,chrono::milliseconds maxTaskTime)`            | Randoms the time task.
`public int `[`main`](#samples_2profile_2main_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()`            | Mains this instance.
`public int `[`main`](#tests_2multi__threaded__detector_2main_8cpp_1a3c04138a5bfe5d72780bb7e82a18e627)`(int argc,char ** argv)`            | 
`namespace `[`task_scheduler`](#namespacetask__scheduler) | Class [stl_allocator](#classtask__scheduler_1_1stl__allocator).
`namespace `[`task_scheduler::atomics`](#namespacetask__scheduler_1_1atomics) | The atomics namespace.
`namespace `[`task_scheduler::profile`](#namespacetask__scheduler_1_1profile) | 
`namespace `[`task_scheduler::profile::thread`](#namespacetask__scheduler_1_1profile_1_1thread) | 
`class `[`task_scheduler::base_task_graph::task_queue_type`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type) | 
`struct `[`task_scheduler::lock_free_node_stack::debug_container`](#structtask__scheduler_1_1lock__free__node__stack_1_1debug__container) | 
`struct `[`task_scheduler::multi_producer_multi_consumer::debug_container`](#structtask__scheduler_1_1multi__producer__multi__consumer_1_1debug__container) | 
`struct `[`task_scheduler::base_task::debug_container`](#structtask__scheduler_1_1base__task_1_1debug__container) | Struct [debug_container](#structtask__scheduler_1_1base__task_1_1debug__container)
`struct `[`task_scheduler::base_task_graph::debug_container`](#structtask__scheduler_1_1base__task__graph_1_1debug__container) | Struct [debug_container](#structtask__scheduler_1_1base__task__graph_1_1debug__container)
`struct `[`task_scheduler::default_mem_interface::metadata_type`](#structtask__scheduler_1_1default__mem__interface_1_1metadata__type) | Struct metadata_type
`struct `[`task_scheduler::base_task_graph::persistent_container`](#structtask__scheduler_1_1base__task__graph_1_1persistent__container) | Struct [persistent_container](#structtask__scheduler_1_1base__task__graph_1_1persistent__container)
`struct `[`task_scheduler::base_task::persistent_container`](#structtask__scheduler_1_1base__task_1_1persistent__container) | Struct [persistent_container](#structtask__scheduler_1_1base__task_1_1persistent__container)
`struct `[`task_scheduler::stl_allocator::rebind`](#structtask__scheduler_1_1stl__allocator_1_1rebind) | Struct rebind
`struct `[`task_scheduler::base_thread_pool::setup_container`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container) | Struct [setup_container](#structtask__scheduler_1_1base__thread__pool_1_1setup__container)
`struct `[`task_scheduler::base_task::transient_container`](#structtask__scheduler_1_1base__task_1_1transient__container) | Struct [transient_container](#structtask__scheduler_1_1base__task_1_1transient__container)
`struct `[`task_scheduler::base_task_graph::transient_container`](#structtask__scheduler_1_1base__task__graph_1_1transient__container) | Struct [transient_container](#structtask__scheduler_1_1base__task__graph_1_1transient__container)
`struct `[`task_scheduler::base_data_task::transient_data_container`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container) | 
`union `[`task_scheduler::atomic_lock_free_node_ptr::Data`](#uniontask__scheduler_1_1atomic__lock__free__node__ptr_1_1Data) | 
`union `[`task_scheduler::guarded_write_array::flags`](#uniontask__scheduler_1_1guarded__write__array_1_1flags) | 

## Members

#### `define `[`ALIGNMENT`](#alignment_8h_1a450f9d8af07bfe2f313dbe3a78738a5e) 

#### `define `[`class_alignment`](#containers_8h_1a260ce407668618187dc13842c095a647) 

#### `define `[`TASK_SCHEDULER_DISABLED`](#defines_8h_1ae9b1df2b104a6682d02254d8504aa3cb) 

#### `define `[`TASK_SCHEDULER_ENABLED`](#defines_8h_1a78dd1c60aa9944594bfdc56e78389a38) 

#### `define `[`TASK_SCHEDULER_PROFILER_NONE`](#defines_8h_1aafdb6b6d5c1d278e51de4dc7eab6ba5f) 

#### `define `[`TASK_SCHEDULER_PROFILER_ITT`](#defines_8h_1ae6c55a565b1fa61326e3b687971e7137) 

#### `define `[`task_scheduler_default_mem_interface_catch_all_allocations`](#memory_8h_1a7908572757e9ecd35e78b16de28f5b43) 

#### `define `[`optimization`](#meta_8h_1a9ff5da7d3d16a1bd047a76e2d68782f0) 

#### `define `[`reduce_starvation`](#meta_8h_1a4baf8b0d017cab46679be16a6a456eb2) 

#### `define `[`ts_windows_only`](#platform_8h_1a372ddc9444b8d67b78ca4390bc16eaf3) 

#### `define `[`tchar_t`](#platform_8h_1acf7a0908ceed3a6ad09958993aae6868) 

#### `define `[`_t`](#platform_8h_1aabc341906992e6fc99ffb879df3003c7) 

#### `define `[`ts_print_internal`](#print_8h_1a17099dcee86b45b08093146e333907a3) 

#### `define `[`ts_print`](#print_8h_1a52e7a19f22557adf8886357947f0b815) 

#### `define `[`ts_debug_only`](#utils_8h_1a569b826ad125451b8358c4a0385fb985) 

#### `define `[`ts_assert`](#utils_8h_1a025700f763a0dbb62173ab080884329a) 

#### `define `[`ts_always_assert`](#utils_8h_1a59627301966eb7bd49bf4860004823d9) 

#### `define `[`ts_itt`](#utils_8h_1a6bab8188114862bfcf8ad054c7135389) 

#### `define `[`ts_join_string`](#utils_8h_1ac9491a767789204698d1ee7b1f3ac863) 

#### `define `[`ts_do_join`](#utils_8h_1aaafd1202c51b64c616032d417fe64fd9) 

#### `define `[`ts_unique_variable`](#utils_8h_1ab33a568c06366a76235b9a5a01e6226e) 

#### `define `[`ts_unused`](#utils_8h_1a5755c9df6d339aa6eb1a303ac9ba6601) 

#### `define `[`ts_declare_attribute_and_callbacks`](#utils_8h_1a7c3470866bab76b82670a8bcf3b7f2e9) 

#### `define `[`ts_init_attribute_and_callbacks`](#utils_8h_1adc341c494347f788c80023428fc411de) 

#### `define `[`ts_declare_attribute`](#utils_8h_1a3b90c42ae60ecb4871d3bb47ebe7970a) 

#### `define `[`ts_init_attribute`](#utils_8h_1a42d958decfcd15195b2a488247dde6ee) 

#### `define `[`TASK_SCHEDULER_PROFILER`](#tests_2multi__threaded__detector_2main_8cpp_1a9ea10af1191c1eec7fde05db51f5aab4) 

#### `define `[`TASK_SCHEDULER_DEBUG`](#samples_2basic_2stdafx_8h_1ac413d9542a19405f74c6699450163a7b) 

#### `define `[`TASK_SCHEDULER_ASSERT`](#samples_2basic_2stdafx_8h_1abd956a528a775769f07ab5af25d83ef3) 

#### `define `[`TASK_SCHEDULER_PROFILER`](#samples_2basic_2stdafx_8h_1a9ea10af1191c1eec7fde05db51f5aab4) 

#### `define `[`TASK_SCHEDULER_DEBUG`](#samples_2profile_2stdafx_8h_1ac413d9542a19405f74c6699450163a7b) 

#### `define `[`TASK_SCHEDULER_ASSERT`](#samples_2profile_2stdafx_8h_1abd956a528a775769f07ab5af25d83ef3) 

#### `define `[`TASK_SCHEDULER_PROFILER`](#samples_2profile_2stdafx_8h_1a9ea10af1191c1eec7fde05db51f5aab4) 

#### `define `[`TASK_SCHEDULER_DEBUG`](#tests_2multi__threaded__detector_2stdafx_8h_1ac413d9542a19405f74c6699450163a7b) 

#### `define `[`TASK_SCHEDULER_ASSERT`](#tests_2multi__threaded__detector_2stdafx_8h_1abd956a528a775769f07ab5af25d83ef3) 

#### `public  `[`task_scheduler_default_mem_interface_catch_all_allocations`](#samples_2basic_2main_8cpp_1ade4ab2d33186fff4f511f0b6b946acca)`()` 

#### `public void `[`RandomTimeTask`](#samples_2basic_2main_8cpp_1a1965f00a1f57e9a7ac227a5278eefd3b)`(chrono::milliseconds minTaskTime,chrono::milliseconds maxTaskTime)` 

Randoms the time task.

#### Parameters
* `minTaskTime` The minimum task time.

* `maxTaskTime` The maximum task time.

#### `public int `[`main`](#samples_2basic_2main_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()` 

Mains this instance.

#### Returns
int.

#### `public  `[`task_scheduler_default_mem_interface_catch_all_allocations`](#samples_2profile_2main_8cpp_1ade4ab2d33186fff4f511f0b6b946acca)`()` 

#### `public void `[`RandomTimeTask`](#samples_2profile_2main_8cpp_1a1965f00a1f57e9a7ac227a5278eefd3b)`(chrono::milliseconds minTaskTime,chrono::milliseconds maxTaskTime)` 

Randoms the time task.

#### Parameters
* `minTaskTime` The minimum task time.

* `maxTaskTime` The maximum task time.

#### `public int `[`main`](#samples_2profile_2main_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()` 

Mains this instance.

#### Returns
int.

#### `public int `[`main`](#tests_2multi__threaded__detector_2main_8cpp_1a3c04138a5bfe5d72780bb7e82a18e627)`(int argc,char ** argv)` 

# namespace `task_scheduler` 

Class [stl_allocator](#classtask__scheduler_1_1stl__allocator).

The [task_scheduler](#namespacetask__scheduler) namespace. 

**See also**: TMemInterface

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t `[`get_cache_line_size`](#namespacetask__scheduler_1a699930ce1c7bbb665905c7bbf4c1f6fd)`()`            | Gets the size of the cache line.
`public inline uint8_t `[`get_thread_number`](#namespacetask__scheduler_1a69b3544305b517d91376e65f097c1af3)`()`            | Gets the thread number.
`public template<>`  <br/>`T * `[`get_current_thread`](#namespacetask__scheduler_1a9e06fa00a344a52247992fd801f6c58c)`()`            | Gets the current thread.
`public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator+`](#namespacetask__scheduler_1ae6c64e364b1f5c8b19969907012f2343)`(`[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > lhs,const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > & rhs)`            | #### Parameters
`public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator+`](#namespacetask__scheduler_1a278e40f7405cbb715661c06db6ff1a33)`(`[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > lhs,int32_t rhs)`            | 
`public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator+`](#namespacetask__scheduler_1a38bcb9db8a59e7dc45eccd62e0624db7)`(int32_t lhs,const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > & rhs)`            | 
`public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator-`](#namespacetask__scheduler_1ad9fc791a5d43ed948a7a95be0ed59f09)`(`[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > lhs,const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > & rhs)`            | 
`public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator-`](#namespacetask__scheduler_1ad6053d852ea996caa78d7e0ed12fb5c4)`(`[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > lhs,int32_t rhs)`            | 
`public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator-`](#namespacetask__scheduler_1a150479dd8f0ba495dcbfe0f101710647)`(int32_t lhs,const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > & rhs)`            | 
`public inline thread_mask_int_t `[`create_mask_64`](#namespacetask__scheduler_1ab3a736b09ac22f58cb3cee50176a9f8d)`()`            | Creates the mask 64.
`public template<>`  <br/>`thread_mask_int_t `[`create_mask_64`](#namespacetask__scheduler_1a3736854334b1289d1b0264468b14cd8b)`(T first,Args... args)`            | Creates the mask 64.
`public template<>`  <br/>`inline TInterface * `[`get`](#namespacetask__scheduler_1abc53cf81c190f711115eafc382881f62)`()`            | 
`public template<>`  <br/>`inline TAsType * `[`get_as`](#namespacetask__scheduler_1afc32d6e13fcb4f358dc9d34bd44a6c92)`()`            | 
`public template<>`  <br/>`TInterface * `[`create`](#namespacetask__scheduler_1a9c567f53f14f63a2ad7a6b3130f02c26)`()`            | 
`public template<>`  <br/>`void `[`destroy`](#namespacetask__scheduler_1a104f606d4a933b3635a8e09da2486e35)`(TInterface * _interface)`            | 
`class `[`task_scheduler::alarm`](#classtask__scheduler_1_1alarm) | 
`class `[`task_scheduler::attribute`](#classtask__scheduler_1_1attribute) | 
`class `[`task_scheduler::attribute< TOwnerClass, const tchar_t * >`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4) | 
`class `[`task_scheduler::base_data_task`](#classtask__scheduler_1_1base__data__task) | 
`class `[`task_scheduler::base_scoped_param`](#classtask__scheduler_1_1base__scoped__param) | 
`class `[`task_scheduler::base_task`](#classtask__scheduler_1_1base__task) | Class [base_task](#classtask__scheduler_1_1base__task).
`class `[`task_scheduler::base_task_events`](#classtask__scheduler_1_1base__task__events) | 
`class `[`task_scheduler::base_task_graph`](#classtask__scheduler_1_1base__task__graph) | Class [base_task_graph](#classtask__scheduler_1_1base__task__graph).
`class `[`task_scheduler::base_task_graph_helper`](#classtask__scheduler_1_1base__task__graph__helper) | 
`class `[`task_scheduler::base_thread_index`](#classtask__scheduler_1_1base__thread__index) | 
`class `[`task_scheduler::base_thread_pool`](#classtask__scheduler_1_1base__thread__pool) | Class [base_thread_pool](#classtask__scheduler_1_1base__thread__pool).
`class `[`task_scheduler::base_worker_task`](#classtask__scheduler_1_1base__worker__task) | 
`class `[`task_scheduler::constrained`](#classtask__scheduler_1_1constrained) | Class constrained.
`class `[`task_scheduler::default_mem_interface`](#classtask__scheduler_1_1default__mem__interface) | Class [default_mem_interface](#classtask__scheduler_1_1default__mem__interface).
`class `[`task_scheduler::dummy`](#classtask__scheduler_1_1dummy) | 
`class `[`task_scheduler::event`](#classtask__scheduler_1_1event) | 
`class `[`task_scheduler::globals`](#classtask__scheduler_1_1globals) | class globals
`class `[`task_scheduler::guarded`](#classtask__scheduler_1_1guarded) | 
`class `[`task_scheduler::guarded_write_array`](#classtask__scheduler_1_1guarded__write__array) | 
`class `[`task_scheduler::lock_free_batch_dispatcher`](#classtask__scheduler_1_1lock__free__batch__dispatcher) | Class [lock_free_batch_dispatcher](#classtask__scheduler_1_1lock__free__batch__dispatcher).
`class `[`task_scheduler::lock_free_node_dispenser`](#classtask__scheduler_1_1lock__free__node__dispenser) | 
`class `[`task_scheduler::lock_free_node_stack`](#classtask__scheduler_1_1lock__free__node__stack) | 
`class `[`task_scheduler::lock_free_queue`](#classtask__scheduler_1_1lock__free__queue) | 
`class `[`task_scheduler::lock_free_stack`](#classtask__scheduler_1_1lock__free__stack) | 
`class `[`task_scheduler::multi_producer_multi_consumer`](#classtask__scheduler_1_1multi__producer__multi__consumer) | 
`class `[`task_scheduler::scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit) | Class [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit).
`class `[`task_scheduler::scoped_enter_exit< TClassType, base_scoped_param >`](#classtask__scheduler_1_1scoped__enter__exit_3_01TClassType_00_01base__scoped__param_01_4) | 
`class `[`task_scheduler::stl_allocator`](#classtask__scheduler_1_1stl__allocator) | 
`class `[`task_scheduler::unsafe_multi_threaded_access_detector`](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector) | Class [unsafe_multi_threaded_access_detector](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector).
`struct `[`task_scheduler::atomic_lock_free_node`](#structtask__scheduler_1_1atomic__lock__free__node) | 
`struct `[`task_scheduler::atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr) | 
`struct `[`task_scheduler::base_sub_graph`](#structtask__scheduler_1_1base__sub__graph) | Struct [base_sub_graph](#structtask__scheduler_1_1base__sub__graph)
`struct `[`task_scheduler::base_thread`](#structtask__scheduler_1_1base__thread) | Struct [base_thread](#structtask__scheduler_1_1base__thread)
`struct `[`task_scheduler::lock_free_node`](#structtask__scheduler_1_1lock__free__node) | 
`struct `[`task_scheduler::out_t`](#structtask__scheduler_1_1out__t) | Struct [out_t](#structtask__scheduler_1_1out__t)
`struct `[`task_scheduler::thread_unsafe_access_storage`](#structtask__scheduler_1_1thread__unsafe__access__storage) | Struct [thread_unsafe_access_storage](#structtask__scheduler_1_1thread__unsafe__access__storage)
`union `[`task_scheduler::address`](#uniontask__scheduler_1_1address) | 

## Members

#### `public uint32_t `[`get_cache_line_size`](#namespacetask__scheduler_1a699930ce1c7bbb665905c7bbf4c1f6fd)`()` 

Gets the size of the cache line.

#### Returns
uint32_t.

#### `public inline uint8_t `[`get_thread_number`](#namespacetask__scheduler_1a69b3544305b517d91376e65f097c1af3)`()` 

Gets the thread number.

#### Returns
uint8_t.

#### `public template<>`  <br/>`T * `[`get_current_thread`](#namespacetask__scheduler_1a9e06fa00a344a52247992fd801f6c58c)`()` 

Gets the current thread.

#### Returns
T *.

#### `public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator+`](#namespacetask__scheduler_1ae6c64e364b1f5c8b19969907012f2343)`(`[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > lhs,const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > & rhs)` 

#### Parameters
* `lhs` The LHS.

* `rhs` The RHS.

#### Returns
[task_scheduler.base_thread_index](#classtask__scheduler_1_1base__thread__index)<ValueType, TMemInterface>.

#### `public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator+`](#namespacetask__scheduler_1a278e40f7405cbb715661c06db6ff1a33)`(`[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > lhs,int32_t rhs)` 

#### `public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator+`](#namespacetask__scheduler_1a38bcb9db8a59e7dc45eccd62e0624db7)`(int32_t lhs,const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > & rhs)` 

#### `public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator-`](#namespacetask__scheduler_1ad9fc791a5d43ed948a7a95be0ed59f09)`(`[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > lhs,const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > & rhs)` 

#### `public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator-`](#namespacetask__scheduler_1ad6053d852ea996caa78d7e0ed12fb5c4)`(`[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > lhs,int32_t rhs)` 

#### `public template<>`  <br/>`inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > `[`operator-`](#namespacetask__scheduler_1a150479dd8f0ba495dcbfe0f101710647)`(int32_t lhs,const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)`< ValueType, TMemInterface > & rhs)` 

#### `public inline thread_mask_int_t `[`create_mask_64`](#namespacetask__scheduler_1ab3a736b09ac22f58cb3cee50176a9f8d)`()` 

Creates the mask 64.

#### Returns
thread_mask_int_t.

#### `public template<>`  <br/>`thread_mask_int_t `[`create_mask_64`](#namespacetask__scheduler_1a3736854334b1289d1b0264468b14cd8b)`(T first,Args... args)` 

Creates the mask 64.

#### Parameters
* `first` The first.

* `...args` The ...args.

#### Returns
thread_mask_int_t.

#### `public template<>`  <br/>`inline TInterface * `[`get`](#namespacetask__scheduler_1abc53cf81c190f711115eafc382881f62)`()` 

#### `public template<>`  <br/>`inline TAsType * `[`get_as`](#namespacetask__scheduler_1afc32d6e13fcb4f358dc9d34bd44a6c92)`()` 

#### `public template<>`  <br/>`TInterface * `[`create`](#namespacetask__scheduler_1a9c567f53f14f63a2ad7a6b3130f02c26)`()` 

#### `public template<>`  <br/>`void `[`destroy`](#namespacetask__scheduler_1a104f606d4a933b3635a8e09da2486e35)`(TInterface * _interface)` 

# class `task_scheduler::alarm` 

```
class task_scheduler::alarm
  : protected task_scheduler::event
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`alarm`](#classtask__scheduler_1_1alarm_1a7628ae7774e3af93b3dcb1c47a88729f)`()` | 
`public inline void `[`sleep`](#classtask__scheduler_1_1alarm_1a057b4a159647a0bbce51312b79ff864e)`(wake_up_function _wake_up_func)` | 
`public inline void `[`wake_up`](#classtask__scheduler_1_1alarm_1a71f109f4a850096c3ee15a1fe3ca8190)`()` | 
`protected bool `[`sleeping`](#classtask__scheduler_1_1alarm_1abb9ca073c6726c12e8262770927881ae) | 
`typedef `[`wake_up_function`](#classtask__scheduler_1_1alarm_1a72b12e9f9972ad0478cb63783a579f8b) | 

## Members

#### `public inline  `[`alarm`](#classtask__scheduler_1_1alarm_1a7628ae7774e3af93b3dcb1c47a88729f)`()` 

#### `public inline void `[`sleep`](#classtask__scheduler_1_1alarm_1a057b4a159647a0bbce51312b79ff864e)`(wake_up_function _wake_up_func)` 

#### `public inline void `[`wake_up`](#classtask__scheduler_1_1alarm_1a71f109f4a850096c3ee15a1fe3ca8190)`()` 

#### `protected bool `[`sleeping`](#classtask__scheduler_1_1alarm_1abb9ca073c6726c12e8262770927881ae) 

#### `typedef `[`wake_up_function`](#classtask__scheduler_1_1alarm_1a72b12e9f9972ad0478cb63783a579f8b) 

# class `task_scheduler::attribute` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`attribute`](#classtask__scheduler_1_1attribute_1a7882653bdb461b7189db51fab46e271c)`(TType _val,TOwnerClass * _owner,typename TGetFunc _get_func,typename TSetFunc _set_func)` | 
`public  `[`operator TType`](#classtask__scheduler_1_1attribute_1ac9a72faae722c9f1aeed28804ab9b4a7)`()` | 
`public TType & `[`operator=`](#classtask__scheduler_1_1attribute_1a73a11cb84d9593dabb8fab53f3afc07b)`(const TType & _other_val)` | 
`protected TType `[`val`](#classtask__scheduler_1_1attribute_1af9cd8e30843078c266a8d721496969c3) | 
`protected TGetFunc `[`get_func`](#classtask__scheduler_1_1attribute_1afcdc07801b155e2236a541ed25e0bd91) | 
`protected TSetFunc `[`set_func`](#classtask__scheduler_1_1attribute_1a7288be20aae4c9efc76f9d26b3620e71) | 
`protected TOwnerClass * `[`owner`](#classtask__scheduler_1_1attribute_1abec4108cc6b1c3cba1422bbdeacb2cb6) | 
`protected TType * `[`operator &`](#classtask__scheduler_1_1attribute_1ad3a0c5d7310e5fa9e17728366cac7c36)`()` | 

## Members

#### `public  `[`attribute`](#classtask__scheduler_1_1attribute_1a7882653bdb461b7189db51fab46e271c)`(TType _val,TOwnerClass * _owner,typename TGetFunc _get_func,typename TSetFunc _set_func)` 

#### `public  `[`operator TType`](#classtask__scheduler_1_1attribute_1ac9a72faae722c9f1aeed28804ab9b4a7)`()` 

#### `public TType & `[`operator=`](#classtask__scheduler_1_1attribute_1a73a11cb84d9593dabb8fab53f3afc07b)`(const TType & _other_val)` 

#### `protected TType `[`val`](#classtask__scheduler_1_1attribute_1af9cd8e30843078c266a8d721496969c3) 

#### `protected TGetFunc `[`get_func`](#classtask__scheduler_1_1attribute_1afcdc07801b155e2236a541ed25e0bd91) 

#### `protected TSetFunc `[`set_func`](#classtask__scheduler_1_1attribute_1a7288be20aae4c9efc76f9d26b3620e71) 

#### `protected TOwnerClass * `[`owner`](#classtask__scheduler_1_1attribute_1abec4108cc6b1c3cba1422bbdeacb2cb6) 

#### `protected TType * `[`operator &`](#classtask__scheduler_1_1attribute_1ad3a0c5d7310e5fa9e17728366cac7c36)`()` 

# class `task_scheduler::attribute< TOwnerClass, const tchar_t * >` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`attribute`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1ada80ed517c2dc62e7b545ab54830f4e1)`(const tchar_t * _val,TOwnerClass * _owner,typename TGetFunc _get_func,typename TSetFunc _set_func)` | 
`public  `[`operator const tchar_t *`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1ae3faf426c15d99d5efa7a2b00b1e64f2)`()` | 
`public `[`attribute`](#classtask__scheduler_1_1attribute)`< TOwnerClass, const tchar_t * > & `[`operator=`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1ad54d8c4d05e1499893c2a9e7429cd914)`(const tchar_t * _other_val)` | 
`protected tstring `[`val`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a82f3b8feffd0953fe0be880694df3279) | 
`protected TGetFunc `[`get_func`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a5dac4647de0621221219214b27a44b3a) | 
`protected TSetFunc `[`set_func`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a7bb48707bcbd41aeb5d01c708885c4cc) | 
`protected TOwnerClass * `[`owner`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a8627b8d14e8957e1e548adba87fc7240) | 
`protected tstring * `[`operator &`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a1996ee4323a6de5328744369287f8476)`()` | 

## Members

#### `public  `[`attribute`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1ada80ed517c2dc62e7b545ab54830f4e1)`(const tchar_t * _val,TOwnerClass * _owner,typename TGetFunc _get_func,typename TSetFunc _set_func)` 

#### `public  `[`operator const tchar_t *`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1ae3faf426c15d99d5efa7a2b00b1e64f2)`()` 

#### `public `[`attribute`](#classtask__scheduler_1_1attribute)`< TOwnerClass, const tchar_t * > & `[`operator=`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1ad54d8c4d05e1499893c2a9e7429cd914)`(const tchar_t * _other_val)` 

#### `protected tstring `[`val`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a82f3b8feffd0953fe0be880694df3279) 

#### `protected TGetFunc `[`get_func`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a5dac4647de0621221219214b27a44b3a) 

#### `protected TSetFunc `[`set_func`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a7bb48707bcbd41aeb5d01c708885c4cc) 

#### `protected TOwnerClass * `[`owner`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a8627b8d14e8957e1e548adba87fc7240) 

#### `protected tstring * `[`operator &`](#classtask__scheduler_1_1attribute_3_01TOwnerClass_00_01const_01tchar__t_01_5_01_4_1a1996ee4323a6de5328744369287f8476)`()` 

# class `task_scheduler::base_data_task` 

```
class task_scheduler::base_data_task
  : public task_scheduler::base_task< TMemInterface >
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public transient_data_container `[`data_transient`](#classtask__scheduler_1_1base__data__task_1ada6814dc6b997941ff939d5d4a7d1c2c) | The transient
`public  `[`base_data_task`](#classtask__scheduler_1_1base__data__task_1a269a193a2a972755ff25276bc977f2e5)`(typename `[`super::task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & _task_graph,size_t _max_data_parallel_workload)` | Initializes a new instance of the [base_task](#classtask__scheduler_1_1base__task) class.
`public  `[`~base_data_task`](#classtask__scheduler_1_1base__data__task_1abc1a100e2863c8bdbef3a29041a7e8b3)`()` | Finalizes an instance of the [base_task](#classtask__scheduler_1_1base__task) class.
`public bool `[`add_data_parallel_work`](#classtask__scheduler_1_1base__data__task_1a13a3af9ced54b2b2b9493d101a034e39)`(typename data_vector::iterator _begin,typename data_vector::iterator _end)` | Add data parallel work class.
`protected virtual bool `[`run`](#classtask__scheduler_1_1base__data__task_1a38ef0b8eae25959c6b7ff777189030d1)`()` | Callback to run task
`protected virtual void `[`before_scheduled`](#classtask__scheduler_1_1base__data__task_1af1f43c0f832a2ed808dbb2504a1ca8dd)`(thread_num_t _scheduled_on_num_workers)` | Callback is called when a task is scheduled
`protected virtual void `[`after_run`](#classtask__scheduler_1_1base__data__task_1a6d168d88c23f0503423f476bd8f26996)`()` | Callback is called after a task is run
`protected virtual thread_num_t `[`get_recommended_num_workers`](#classtask__scheduler_1_1base__data__task_1a98660ff3a3c8085eb594373b323fc460)`()` | Gets the best number of workers for the task every frame

## Members

#### `public transient_data_container `[`data_transient`](#classtask__scheduler_1_1base__data__task_1ada6814dc6b997941ff939d5d4a7d1c2c) 

The transient

#### `public  `[`base_data_task`](#classtask__scheduler_1_1base__data__task_1a269a193a2a972755ff25276bc977f2e5)`(typename `[`super::task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & _task_graph,size_t _max_data_parallel_workload)` 

Initializes a new instance of the [base_task](#classtask__scheduler_1_1base__task) class.

#### Parameters
* `_task_graph` The task graph.

#### `public  `[`~base_data_task`](#classtask__scheduler_1_1base__data__task_1abc1a100e2863c8bdbef3a29041a7e8b3)`()` 

Finalizes an instance of the [base_task](#classtask__scheduler_1_1base__task) class.

#### `public bool `[`add_data_parallel_work`](#classtask__scheduler_1_1base__data__task_1a13a3af9ced54b2b2b9493d101a034e39)`(typename data_vector::iterator _begin,typename data_vector::iterator _end)` 

Add data parallel work class.

#### Parameters
* `_begin` Iterator to the start of a range of elements to add

* `_begin` Iterator to the end of a range of elements to add

#### `protected virtual bool `[`run`](#classtask__scheduler_1_1base__data__task_1a38ef0b8eae25959c6b7ff777189030d1)`()` 

Callback to run task

#### `protected virtual void `[`before_scheduled`](#classtask__scheduler_1_1base__data__task_1af1f43c0f832a2ed808dbb2504a1ca8dd)`(thread_num_t _scheduled_on_num_workers)` 

Callback is called when a task is scheduled

#### `protected virtual void `[`after_run`](#classtask__scheduler_1_1base__data__task_1a6d168d88c23f0503423f476bd8f26996)`()` 

Callback is called after a task is run

#### `protected virtual thread_num_t `[`get_recommended_num_workers`](#classtask__scheduler_1_1base__data__task_1a98660ff3a3c8085eb594373b323fc460)`()` 

Gets the best number of workers for the task every frame

#### Parameters
* `_num_workers` The number workers.

# class `task_scheduler::base_scoped_param` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `task_scheduler::base_task` 

```
class task_scheduler::base_task
  : public TMemInterface
  : public task_scheduler::base_task_events
```  

Class [base_task](#classtask__scheduler_1_1base__task).

**See also**: TMemInterface

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`debug_container`](#structtask__scheduler_1_1base__task_1_1debug__container)` `[`debug`](#classtask__scheduler_1_1base__task_1a70fe39ab85376c5d7de87ac91862b2a2) | The debug
`public `[`transient_container`](#structtask__scheduler_1_1base__task_1_1transient__container)` `[`transient`](#classtask__scheduler_1_1base__task_1a7aadaa41211032911bdfb656eebef55e) | The transient
`public `[`persistent_container`](#structtask__scheduler_1_1base__task_1_1persistent__container)` `[`persistent`](#classtask__scheduler_1_1base__task_1ad72a8a112fbbe95284b8df45567e35ee) | The persistent
`public `[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & `[`task_graph`](#classtask__scheduler_1_1base__task_1af87641d48b46d5fbfe43f479cc258ba3) | The task graph
`public `[`thread_unsafe_access_storage`](#structtask__scheduler_1_1thread__unsafe__access__storage)` `[`add_task_parallel_work_detector`](#classtask__scheduler_1_1base__task_1a5177ec452f475a38bc70afcacef59f27) | The add task parallel work detector
`public  `[`base_task`](#classtask__scheduler_1_1base__task_1a85e3c58da21833c5ffecc9036f6ecbc6)`(`[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & _task_graph)` | Initializes a new instance of the [base_task](#classtask__scheduler_1_1base__task) class.
`public virtual  `[`~base_task`](#classtask__scheduler_1_1base__task_1a67ece38ebd9b5ca3c22bfa7c7367e5de)`()` | Finalizes an instance of the [base_task](#classtask__scheduler_1_1base__task) class.
`public void `[`set_thread_affinity`](#classtask__scheduler_1_1base__task_1a795c902be0b14fdf3bde8954a2c83019)`(thread_mask_int_t _mask)` | Sets the thread affinity.
`public void `[`set_thread_exclusion`](#classtask__scheduler_1_1base__task_1a6106e60f73d534c283400c05501a7cd5)`(thread_mask_int_t _mask)` | Sets the thread exclusion.
`public void `[`set_num_workers`](#classtask__scheduler_1_1base__task_1a51a212d9630799ff0857765406641ef5)`(thread_num_t _num_workers)` | Sets the number workers.
`public void `[`set_num_workers`](#classtask__scheduler_1_1base__task_1ad5adb3c581013cc59808319d50d198e3)`(`[`percentage_t`](#classtask__scheduler_1_1constrained)` _percentage_workers)` | Sets the number workers.
`public void `[`kick_dependent_tasks`](#classtask__scheduler_1_1base__task_1a9d4915cb780aa7d01b8c024a5567a136)`()` | Kicks the dependent tasks.
`public bool `[`add_task_parallel_work`](#classtask__scheduler_1_1base__task_1a7d6d7de710db4b369eb2af6ba63681e5)`(function_type _work_function)` | Adds the task parallel work.
`public bool `[`link_task`](#classtask__scheduler_1_1base__task_1a2a8ded8df1d3941df91359013c9ad971)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _next_task)` | Links the task.
`public bool `[`operator()`](#classtask__scheduler_1_1base__task_1a0086886a7abcb49e383def8abf7b6d95)`()` | Operator()s this instance.
`public virtual thread_num_t `[`get_recommended_num_workers`](#classtask__scheduler_1_1base__task_1a1913adff314e5df400b005e941e4d6a9)`()` | Gets the best number of workers for the task every frame
`protected bool `[`run`](#classtask__scheduler_1_1base__task_1a9640ac25d1be1203cb5d48b001747794)`()` | Calls the working function internally
`protected virtual void `[`before_scheduled`](#classtask__scheduler_1_1base__task_1adf94510dc4a7ffd412737c0475718d55)`(thread_num_t _scheduled_on_num_workers)` | Callback is called when a task is scheduled
`protected virtual void `[`after_run`](#classtask__scheduler_1_1base__task_1a14a4ec418f670a861b8f801a8b1a7e17)`()` | Callback is called after a task is run
`enum `[`priority_selector`](#classtask__scheduler_1_1base__task_1aed4fc159d6bb04b606879e7930612eda) | Enum priority_selector
`typedef `[`task_type`](#classtask__scheduler_1_1base__task_1aa32239a6c10d7dfe530d867724d46df3) | 
`typedef `[`thread_type`](#classtask__scheduler_1_1base__task_1aa8c91a15141475b6e2fd974fe308478f) | 
`typedef `[`task_graph_type`](#classtask__scheduler_1_1base__task_1a9470de5159afb62816ed9e9e0b06edad) | 
`typedef `[`sub_graph_type`](#classtask__scheduler_1_1base__task_1acf4b9e6a14446d0aa15ac7ce9498dc21) | 
`typedef `[`string_type`](#classtask__scheduler_1_1base__task_1a6f1ddaf4163ff7b2a8b1160109daa61e) | 
`typedef `[`string_vector`](#classtask__scheduler_1_1base__task_1a309e7d8d0675cd9c353b1349b0c0b8d4) | 
`typedef `[`task_vector`](#classtask__scheduler_1_1base__task_1abcfc89bd7dbb8e438d39099474e11129) | 
`typedef `[`thread_pool`](#classtask__scheduler_1_1base__task_1a24742a15a48a52bf4c425be7523c4945) | 
`typedef `[`function_type`](#classtask__scheduler_1_1base__task_1a496395edf36cbd448a49d97a20e34db2) | 
`typedef `[`rank_type`](#classtask__scheduler_1_1base__task_1a72bf447ba08410b75d78c7620dafe19c) | 
`typedef `[`task_work_vector`](#classtask__scheduler_1_1base__task_1a30b70f12e3feecfdef171cfeb184d3d8) | 
`typedef `[`thread_index_type`](#classtask__scheduler_1_1base__task_1a8fb9af3986b6cfb8620a4edade481343) | 
`typedef `[`work_memory_allocator_type`](#classtask__scheduler_1_1base__task_1a2a94a96157202254e6644a4615007550) | 
`typedef `[`work_queue_type`](#classtask__scheduler_1_1base__task_1aa497bf00e5d8264c53a3723d75b281d0) | 

## Members

#### `public `[`debug_container`](#structtask__scheduler_1_1base__task_1_1debug__container)` `[`debug`](#classtask__scheduler_1_1base__task_1a70fe39ab85376c5d7de87ac91862b2a2) 

The debug

#### `public `[`transient_container`](#structtask__scheduler_1_1base__task_1_1transient__container)` `[`transient`](#classtask__scheduler_1_1base__task_1a7aadaa41211032911bdfb656eebef55e) 

The transient

#### `public `[`persistent_container`](#structtask__scheduler_1_1base__task_1_1persistent__container)` `[`persistent`](#classtask__scheduler_1_1base__task_1ad72a8a112fbbe95284b8df45567e35ee) 

The persistent

#### `public `[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & `[`task_graph`](#classtask__scheduler_1_1base__task_1af87641d48b46d5fbfe43f479cc258ba3) 

The task graph

#### `public `[`thread_unsafe_access_storage`](#structtask__scheduler_1_1thread__unsafe__access__storage)` `[`add_task_parallel_work_detector`](#classtask__scheduler_1_1base__task_1a5177ec452f475a38bc70afcacef59f27) 

The add task parallel work detector

#### `public  `[`base_task`](#classtask__scheduler_1_1base__task_1a85e3c58da21833c5ffecc9036f6ecbc6)`(`[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & _task_graph)` 

Initializes a new instance of the [base_task](#classtask__scheduler_1_1base__task) class.

#### Parameters
* `_task_graph` The task graph.

#### `public virtual  `[`~base_task`](#classtask__scheduler_1_1base__task_1a67ece38ebd9b5ca3c22bfa7c7367e5de)`()` 

Finalizes an instance of the [base_task](#classtask__scheduler_1_1base__task) class.

#### `public void `[`set_thread_affinity`](#classtask__scheduler_1_1base__task_1a795c902be0b14fdf3bde8954a2c83019)`(thread_mask_int_t _mask)` 

Sets the thread affinity.

#### Parameters
* `_mask` The mask.

#### `public void `[`set_thread_exclusion`](#classtask__scheduler_1_1base__task_1a6106e60f73d534c283400c05501a7cd5)`(thread_mask_int_t _mask)` 

Sets the thread exclusion.

#### Parameters
* `_mask` The mask.

#### `public void `[`set_num_workers`](#classtask__scheduler_1_1base__task_1a51a212d9630799ff0857765406641ef5)`(thread_num_t _num_workers)` 

Sets the number workers.

#### Parameters
* `_num_workers` The number workers.

#### `public void `[`set_num_workers`](#classtask__scheduler_1_1base__task_1ad5adb3c581013cc59808319d50d198e3)`(`[`percentage_t`](#classtask__scheduler_1_1constrained)` _percentage_workers)` 

Sets the number workers.

#### Parameters
* `_percentage_workers` The percentage workers.

#### `public void `[`kick_dependent_tasks`](#classtask__scheduler_1_1base__task_1a9d4915cb780aa7d01b8c024a5567a136)`()` 

Kicks the dependent tasks.

#### `public bool `[`add_task_parallel_work`](#classtask__scheduler_1_1base__task_1a7d6d7de710db4b369eb2af6ba63681e5)`(function_type _work_function)` 

Adds the task parallel work.

#### Parameters
* `_work_function` The work function.

#### Returns
bool.

#### `public bool `[`link_task`](#classtask__scheduler_1_1base__task_1a2a8ded8df1d3941df91359013c9ad971)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _next_task)` 

Links the task.

#### Parameters
* `_next_task` The next task.

#### Returns
bool.

#### `public bool `[`operator()`](#classtask__scheduler_1_1base__task_1a0086886a7abcb49e383def8abf7b6d95)`()` 

Operator()s this instance.

#### Returns
bool.

#### `public virtual thread_num_t `[`get_recommended_num_workers`](#classtask__scheduler_1_1base__task_1a1913adff314e5df400b005e941e4d6a9)`()` 

Gets the best number of workers for the task every frame

#### Parameters
* `_num_workers` The number workers.

#### `protected bool `[`run`](#classtask__scheduler_1_1base__task_1a9640ac25d1be1203cb5d48b001747794)`()` 

Calls the working function internally

#### Returns
bool.

#### `protected virtual void `[`before_scheduled`](#classtask__scheduler_1_1base__task_1adf94510dc4a7ffd412737c0475718d55)`(thread_num_t _scheduled_on_num_workers)` 

Callback is called when a task is scheduled

#### `protected virtual void `[`after_run`](#classtask__scheduler_1_1base__task_1a14a4ec418f670a861b8f801a8b1a7e17)`()` 

Callback is called after a task is run

#### `enum `[`priority_selector`](#classtask__scheduler_1_1base__task_1aed4fc159d6bb04b606879e7930612eda) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
realtime            | 
high            | 
normal            | 
low            | 
num_priority            | 

Enum priority_selector

#### `typedef `[`task_type`](#classtask__scheduler_1_1base__task_1aa32239a6c10d7dfe530d867724d46df3) 

#### `typedef `[`thread_type`](#classtask__scheduler_1_1base__task_1aa8c91a15141475b6e2fd974fe308478f) 

#### `typedef `[`task_graph_type`](#classtask__scheduler_1_1base__task_1a9470de5159afb62816ed9e9e0b06edad) 

#### `typedef `[`sub_graph_type`](#classtask__scheduler_1_1base__task_1acf4b9e6a14446d0aa15ac7ce9498dc21) 

#### `typedef `[`string_type`](#classtask__scheduler_1_1base__task_1a6f1ddaf4163ff7b2a8b1160109daa61e) 

#### `typedef `[`string_vector`](#classtask__scheduler_1_1base__task_1a309e7d8d0675cd9c353b1349b0c0b8d4) 

#### `typedef `[`task_vector`](#classtask__scheduler_1_1base__task_1abcfc89bd7dbb8e438d39099474e11129) 

#### `typedef `[`thread_pool`](#classtask__scheduler_1_1base__task_1a24742a15a48a52bf4c425be7523c4945) 

#### `typedef `[`function_type`](#classtask__scheduler_1_1base__task_1a496395edf36cbd448a49d97a20e34db2) 

#### `typedef `[`rank_type`](#classtask__scheduler_1_1base__task_1a72bf447ba08410b75d78c7620dafe19c) 

#### `typedef `[`task_work_vector`](#classtask__scheduler_1_1base__task_1a30b70f12e3feecfdef171cfeb184d3d8) 

#### `typedef `[`thread_index_type`](#classtask__scheduler_1_1base__task_1a8fb9af3986b6cfb8620a4edade481343) 

#### `typedef `[`work_memory_allocator_type`](#classtask__scheduler_1_1base__task_1a2a94a96157202254e6644a4615007550) 

#### `typedef `[`work_queue_type`](#classtask__scheduler_1_1base__task_1aa497bf00e5d8264c53a3723d75b281d0) 

# class `task_scheduler::base_task_events` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`before_scheduled`](#classtask__scheduler_1_1base__task__events_1afa96dbf8496936072516189aa6d3f757)`(thread_num_t _scheduled_on_num_workers)` | 
`public void `[`after_run`](#classtask__scheduler_1_1base__task__events_1a51caba2e23f932bb9fd8efca096eabc6)`()` | 

## Members

#### `public void `[`before_scheduled`](#classtask__scheduler_1_1base__task__events_1afa96dbf8496936072516189aa6d3f757)`(thread_num_t _scheduled_on_num_workers)` 

#### `public void `[`after_run`](#classtask__scheduler_1_1base__task__events_1a51caba2e23f932bb9fd8efca096eabc6)`()` 

# class `task_scheduler::base_task_graph` 

```
class task_scheduler::base_task_graph
  : public TMemInterface
```  

Class [base_task_graph](#classtask__scheduler_1_1base__task__graph).

**See also**: TMemInterface

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`persistent_container`](#structtask__scheduler_1_1base__task__graph_1_1persistent__container)` `[`persistent`](#classtask__scheduler_1_1base__task__graph_1af876ab8b8914e6d17dbfc3f265d3a439) | The persistent
`public `[`transient_container`](#structtask__scheduler_1_1base__task__graph_1_1transient__container)` `[`transient`](#classtask__scheduler_1_1base__task__graph_1ac2faf3898153bb339c12b4677ecdd5bc) | The transient
`public `[`debug_container`](#structtask__scheduler_1_1base__task__graph_1_1debug__container)` `[`debug`](#classtask__scheduler_1_1base__task__graph_1af9b085456e20e0be8c940ffd003d4872) | The debug
`public `[`thread_pool`](#classtask__scheduler_1_1base__thread__pool)` & `[`pool`](#classtask__scheduler_1_1base__task__graph_1aef1db5a1a26b77d21d7b635bf0c05912) | The pool
`public  `[`base_task_graph`](#classtask__scheduler_1_1base__task__graph_1aa20fd625175b4491924fbfa7941c13be)`(`[`thread_pool`](#classtask__scheduler_1_1base__thread__pool)` & _pool)` | Initializes a new instance of the [base_task_graph](#classtask__scheduler_1_1base__task__graph) class.
`public  `[`~base_task_graph`](#classtask__scheduler_1_1base__task__graph_1a0012bf8adf5ce028245b642f01d803ec)`()` | Finalizes an instance of the [base_task_graph](#classtask__scheduler_1_1base__task__graph) class.
`public void `[`setup`](#classtask__scheduler_1_1base__task__graph_1a095a4684a6a1a4edde67b2b146b8744c)`(`[`sub_graph_type`](#structtask__scheduler_1_1base__sub__graph)` * _sub_graph)` | Setups the specified sub graph.
`public void `[`load`](#classtask__scheduler_1_1base__task__graph_1a7237b5084d6de2750cd8bcd8eb28caf9)`(string_type _file_name)` | Loads the specified file name.
`public void `[`initialize`](#classtask__scheduler_1_1base__task__graph_1afae74c61dd22f52b20031f0243a6f29c)`()` | Initializes this instance.
`public void `[`set_task_thread_affinity`](#classtask__scheduler_1_1base__task__graph_1a08b48389686027cea396dba14bce3910)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,uint64_t _mask)` | Sets the task thread affinity.
`public void `[`set_task_thread_exclusion`](#classtask__scheduler_1_1base__task__graph_1a9c9f7a5c04f7d4f1bd9ae7f5ef454d10)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,uint64_t _mask)` | Sets the task thread exclusion.
`public void `[`set_num_workers`](#classtask__scheduler_1_1base__task__graph_1ae3c9c64ff7a4fa79d9b0c68eae0c2908)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,thread_num_t _num_workers)` | Sets the number workers.
`public void `[`set_percentage_of_workers`](#classtask__scheduler_1_1base__task__graph_1ab2724abbda51a33554f3cd7882601671)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,float _percentage_workers)` | Sets the percentage of workers.
`public void `[`setup_tail_kickers`](#classtask__scheduler_1_1base__task__graph_1a0a70faa40857327476928fd361195842)`()` | Setups the tail kickers.
`public void `[`depth_first_visitor`](#classtask__scheduler_1_1base__task__graph_1a6b9d01c7f63cb07a063fd2900d675e5f)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,traversal_function_type _preorder_functor,traversal_function_type _inorder_functor,traversal_function_type _post_order_functor,traversal_function_type _tail_functor,void * _param,bool _bottom_up)` | Depthes the first visitor.
`public void `[`kick`](#classtask__scheduler_1_1base__task__graph_1a993e7c3b7ccf836079979336add09364)`()` | Kicks this instance.
`public void `[`queue_task`](#classtask__scheduler_1_1base__task__graph_1a6bd74032573400b2a41d7dffde7c44bd)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,thread_num_t _num_threads_to_wake_up)` | Queues the task.
`public `[`task_type`](#classtask__scheduler_1_1base__task)` * `[`dequeue_task`](#classtask__scheduler_1_1base__task__graph_1a767a818fbb61f45ac611c9342c379538)`(uint32_t _priority)` | Dequeues the task.
`public bool `[`is_task_available`](#classtask__scheduler_1_1base__task__graph_1a89973d25236e80e72d1b95d594e26211)`()` | Determines whether [is task available].
`public bool `[`link_task`](#classtask__scheduler_1_1base__task__graph_1a3154631076348ac62d494daf184cbc40)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _parent_task,`[`task_type`](#classtask__scheduler_1_1base__task)` * _dependent_task)` | Links the task.
`typedef `[`task_type`](#classtask__scheduler_1_1base__task__graph_1ae8cc0d26f5f6c0073197f698cf3905f5) | 
`typedef `[`string_type`](#classtask__scheduler_1_1base__task__graph_1ad74545232c20d9395a086d60c27af302) | 
`typedef `[`sub_graph_type`](#classtask__scheduler_1_1base__task__graph_1a8fd11ead92e3061385f3098504b15609) | 
`typedef `[`task_memory_allocator_type`](#classtask__scheduler_1_1base__task__graph_1a46a0dbc03d1938405f57195ad7c3404f) | 
`typedef `[`base_task_queue_type`](#classtask__scheduler_1_1base__task__graph_1a5d799f3a1cb659a33207d1db583e84c7) | 
`typedef `[`task_name_to_task_map`](#classtask__scheduler_1_1base__task__graph_1a457a62447592a2914c3e14ac2f38a850) | 
`typedef `[`sub_graph_vector`](#classtask__scheduler_1_1base__task__graph_1ab7d3997f7b9ad9a051278aebb9657932) | 
`typedef `[`task_vector`](#classtask__scheduler_1_1base__task__graph_1acfce223f445eb3e5afcb8b28467675e5) | 
`typedef `[`thread_pool`](#classtask__scheduler_1_1base__task__graph_1ac8908fa4e19cb2d52534535227b18bf1) | 
`typedef `[`task_list`](#classtask__scheduler_1_1base__task__graph_1a79c632a2c1443b0e26e1a6c08f1e5a93) | 
`typedef `[`traversal_function_type`](#classtask__scheduler_1_1base__task__graph_1a5966ce91ad7bf508289ab16aa1c4ba46) | 

## Members

#### `public `[`persistent_container`](#structtask__scheduler_1_1base__task__graph_1_1persistent__container)` `[`persistent`](#classtask__scheduler_1_1base__task__graph_1af876ab8b8914e6d17dbfc3f265d3a439) 

The persistent

#### `public `[`transient_container`](#structtask__scheduler_1_1base__task__graph_1_1transient__container)` `[`transient`](#classtask__scheduler_1_1base__task__graph_1ac2faf3898153bb339c12b4677ecdd5bc) 

The transient

#### `public `[`debug_container`](#structtask__scheduler_1_1base__task__graph_1_1debug__container)` `[`debug`](#classtask__scheduler_1_1base__task__graph_1af9b085456e20e0be8c940ffd003d4872) 

The debug

#### `public `[`thread_pool`](#classtask__scheduler_1_1base__thread__pool)` & `[`pool`](#classtask__scheduler_1_1base__task__graph_1aef1db5a1a26b77d21d7b635bf0c05912) 

The pool

#### `public  `[`base_task_graph`](#classtask__scheduler_1_1base__task__graph_1aa20fd625175b4491924fbfa7941c13be)`(`[`thread_pool`](#classtask__scheduler_1_1base__thread__pool)` & _pool)` 

Initializes a new instance of the [base_task_graph](#classtask__scheduler_1_1base__task__graph) class.

#### Parameters
* `_pool` The pool.

#### `public  `[`~base_task_graph`](#classtask__scheduler_1_1base__task__graph_1a0012bf8adf5ce028245b642f01d803ec)`()` 

Finalizes an instance of the [base_task_graph](#classtask__scheduler_1_1base__task__graph) class.

#### `public void `[`setup`](#classtask__scheduler_1_1base__task__graph_1a095a4684a6a1a4edde67b2b146b8744c)`(`[`sub_graph_type`](#structtask__scheduler_1_1base__sub__graph)` * _sub_graph)` 

Setups the specified sub graph.

#### Parameters
* `_sub_graph` The sub graph.

#### `public void `[`load`](#classtask__scheduler_1_1base__task__graph_1a7237b5084d6de2750cd8bcd8eb28caf9)`(string_type _file_name)` 

Loads the specified file name.

#### Parameters
* `_file_name` Name of the file.

#### `public void `[`initialize`](#classtask__scheduler_1_1base__task__graph_1afae74c61dd22f52b20031f0243a6f29c)`()` 

Initializes this instance.

#### `public void `[`set_task_thread_affinity`](#classtask__scheduler_1_1base__task__graph_1a08b48389686027cea396dba14bce3910)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,uint64_t _mask)` 

Sets the task thread affinity.

#### Parameters
* `_task` The task.

* `_mask` The mask.

#### `public void `[`set_task_thread_exclusion`](#classtask__scheduler_1_1base__task__graph_1a9c9f7a5c04f7d4f1bd9ae7f5ef454d10)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,uint64_t _mask)` 

Sets the task thread exclusion.

#### Parameters
* `_task` The task.

* `_mask` The mask.

#### `public void `[`set_num_workers`](#classtask__scheduler_1_1base__task__graph_1ae3c9c64ff7a4fa79d9b0c68eae0c2908)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,thread_num_t _num_workers)` 

Sets the number workers.

#### Parameters
* `_task` The task.

* `_num_workers` The number workers.

#### `public void `[`set_percentage_of_workers`](#classtask__scheduler_1_1base__task__graph_1ab2724abbda51a33554f3cd7882601671)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,float _percentage_workers)` 

Sets the percentage of workers.

#### Parameters
* `_task` The task.

* `_percentage_workers` The percentage workers.

#### `public void `[`setup_tail_kickers`](#classtask__scheduler_1_1base__task__graph_1a0a70faa40857327476928fd361195842)`()` 

Setups the tail kickers.

#### `public void `[`depth_first_visitor`](#classtask__scheduler_1_1base__task__graph_1a6b9d01c7f63cb07a063fd2900d675e5f)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,traversal_function_type _preorder_functor,traversal_function_type _inorder_functor,traversal_function_type _post_order_functor,traversal_function_type _tail_functor,void * _param,bool _bottom_up)` 

Depthes the first visitor.

#### Parameters
* `_task` The task.

* `_preorder_functor` The preorder functor.

* `_inorder_functor` The inorder functor.

* `_post_order_functor` The post order functor.

* `_tail_functor` The tail functor.

* `_param` The parameter.

* `_bottom_up` The bottom up.

#### `public void `[`kick`](#classtask__scheduler_1_1base__task__graph_1a993e7c3b7ccf836079979336add09364)`()` 

Kicks this instance.

#### `public void `[`queue_task`](#classtask__scheduler_1_1base__task__graph_1a6bd74032573400b2a41d7dffde7c44bd)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,thread_num_t _num_threads_to_wake_up)` 

Queues the task.

#### Parameters
* `_task` The task.

* `_num_threads_to_wake_up` The number threads to wake up.

#### `public `[`task_type`](#classtask__scheduler_1_1base__task)` * `[`dequeue_task`](#classtask__scheduler_1_1base__task__graph_1a767a818fbb61f45ac611c9342c379538)`(uint32_t _priority)` 

Dequeues the task.

#### Parameters
* `_priority` The priority.

#### Returns
task_type *.

#### `public bool `[`is_task_available`](#classtask__scheduler_1_1base__task__graph_1a89973d25236e80e72d1b95d594e26211)`()` 

Determines whether [is task available].

#### Returns
bool.

#### `public bool `[`link_task`](#classtask__scheduler_1_1base__task__graph_1a3154631076348ac62d494daf184cbc40)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _parent_task,`[`task_type`](#classtask__scheduler_1_1base__task)` * _dependent_task)` 

Links the task.

#### Parameters
* `_parent_task` The parent task.

* `_dependent_task` The dependent task.

#### Returns
bool.

#### `typedef `[`task_type`](#classtask__scheduler_1_1base__task__graph_1ae8cc0d26f5f6c0073197f698cf3905f5) 

#### `typedef `[`string_type`](#classtask__scheduler_1_1base__task__graph_1ad74545232c20d9395a086d60c27af302) 

#### `typedef `[`sub_graph_type`](#classtask__scheduler_1_1base__task__graph_1a8fd11ead92e3061385f3098504b15609) 

#### `typedef `[`task_memory_allocator_type`](#classtask__scheduler_1_1base__task__graph_1a46a0dbc03d1938405f57195ad7c3404f) 

#### `typedef `[`base_task_queue_type`](#classtask__scheduler_1_1base__task__graph_1a5d799f3a1cb659a33207d1db583e84c7) 

#### `typedef `[`task_name_to_task_map`](#classtask__scheduler_1_1base__task__graph_1a457a62447592a2914c3e14ac2f38a850) 

#### `typedef `[`sub_graph_vector`](#classtask__scheduler_1_1base__task__graph_1ab7d3997f7b9ad9a051278aebb9657932) 

#### `typedef `[`task_vector`](#classtask__scheduler_1_1base__task__graph_1acfce223f445eb3e5afcb8b28467675e5) 

#### `typedef `[`thread_pool`](#classtask__scheduler_1_1base__task__graph_1ac8908fa4e19cb2d52534535227b18bf1) 

#### `typedef `[`task_list`](#classtask__scheduler_1_1base__task__graph_1a79c632a2c1443b0e26e1a6c08f1e5a93) 

#### `typedef `[`traversal_function_type`](#classtask__scheduler_1_1base__task__graph_1a5966ce91ad7bf508289ab16aa1c4ba46) 

# class `task_scheduler::base_task_graph_helper` 

```
class task_scheduler::base_task_graph_helper
  : public TMemInterface
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & `[`task_graph`](#classtask__scheduler_1_1base__task__graph__helper_1ac44610e2be6e79f109611edd4153f8c7) | The task graph
`public  `[`base_task_graph_helper`](#classtask__scheduler_1_1base__task__graph__helper_1a899c67f074377665c54eb48b161f009c)`(`[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & _task_graph)` | Initializes a new instance of the [base_task_graph_helper](#classtask__scheduler_1_1base__task__graph__helper) class.
`public void `[`load`](#classtask__scheduler_1_1base__task__graph__helper_1aece76f631c9dae162fd90f24716f136d)`(string_type _file_name)` | Loads the specified file name.
`public void `[`setup_task`](#classtask__scheduler_1_1base__task__graph__helper_1a47037b3e93600c8f3ec3b0d8759d3463)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,uint32_t _task_file_field,string_type str)` | Setups the task.
`typedef `[`task_type`](#classtask__scheduler_1_1base__task__graph__helper_1a2ff66743782709a0c4d1e15b5c3b5c4a) | 
`typedef `[`worker_task_type`](#classtask__scheduler_1_1base__task__graph__helper_1ad4deca6d83778a429242df2eed249948) | 
`typedef `[`string_type`](#classtask__scheduler_1_1base__task__graph__helper_1aa0e9747db599095cb41e874eb194f243) | 
`typedef `[`task_vector`](#classtask__scheduler_1_1base__task__graph__helper_1a91d633ea90cdba182984661f8707ac71) | 
`typedef `[`thread_pool`](#classtask__scheduler_1_1base__task__graph__helper_1a0e204f3ed04eb72a6d2015f08d692e40) | 
`typedef `[`task_list`](#classtask__scheduler_1_1base__task__graph__helper_1a665071959dc6a96c3a0eed871a422256) | 
`typedef `[`traversal_function_type`](#classtask__scheduler_1_1base__task__graph__helper_1a7aa42bb6fa67471ae9b30d45cbcb7904) | 
`typedef `[`task_graph_type`](#classtask__scheduler_1_1base__task__graph__helper_1ab76fc559f505497a290746e0fd73553f) | 

## Members

#### `public `[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & `[`task_graph`](#classtask__scheduler_1_1base__task__graph__helper_1ac44610e2be6e79f109611edd4153f8c7) 

The task graph

#### `public  `[`base_task_graph_helper`](#classtask__scheduler_1_1base__task__graph__helper_1a899c67f074377665c54eb48b161f009c)`(`[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & _task_graph)` 

Initializes a new instance of the [base_task_graph_helper](#classtask__scheduler_1_1base__task__graph__helper) class.

#### Parameters
* `_task_graph` The task graph.

#### `public void `[`load`](#classtask__scheduler_1_1base__task__graph__helper_1aece76f631c9dae162fd90f24716f136d)`(string_type _file_name)` 

Loads the specified file name.

#### Parameters
* `_file_name` Name of the file.

#### `public void `[`setup_task`](#classtask__scheduler_1_1base__task__graph__helper_1a47037b3e93600c8f3ec3b0d8759d3463)`(`[`task_type`](#classtask__scheduler_1_1base__task)` * _task,uint32_t _task_file_field,string_type str)` 

Setups the task.

#### Parameters
* `_task` The task.

* `_task_file_field` The task file field.

* `str` The string.

#### `typedef `[`task_type`](#classtask__scheduler_1_1base__task__graph__helper_1a2ff66743782709a0c4d1e15b5c3b5c4a) 

#### `typedef `[`worker_task_type`](#classtask__scheduler_1_1base__task__graph__helper_1ad4deca6d83778a429242df2eed249948) 

#### `typedef `[`string_type`](#classtask__scheduler_1_1base__task__graph__helper_1aa0e9747db599095cb41e874eb194f243) 

#### `typedef `[`task_vector`](#classtask__scheduler_1_1base__task__graph__helper_1a91d633ea90cdba182984661f8707ac71) 

#### `typedef `[`thread_pool`](#classtask__scheduler_1_1base__task__graph__helper_1a0e204f3ed04eb72a6d2015f08d692e40) 

#### `typedef `[`task_list`](#classtask__scheduler_1_1base__task__graph__helper_1a665071959dc6a96c3a0eed871a422256) 

#### `typedef `[`traversal_function_type`](#classtask__scheduler_1_1base__task__graph__helper_1a7aa42bb6fa67471ae9b30d45cbcb7904) 

#### `typedef `[`task_graph_type`](#classtask__scheduler_1_1base__task__graph__helper_1ab76fc559f505497a290746e0fd73553f) 

# class `task_scheduler::base_thread_index` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index_1a1f4f899bdce08e5444d3fa383b75fcce)`(`[`thread_pool`](#classtask__scheduler_1_1base__thread__pool)` * _pool,ValueType _value)` | Initializes a new instance of the [base_thread_index](#classtask__scheduler_1_1base__thread__index) class.
`public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator++`](#classtask__scheduler_1_1base__thread__index_1a0fbb1d8170d706a76591a013a3e9cbe4)`()` | Operator++s this instance.
`public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator--`](#classtask__scheduler_1_1base__thread__index_1af4cf457a4b9aa657d41183de1164c0af)`()` | Operators this instance.
`public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator+=`](#classtask__scheduler_1_1base__thread__index_1aa40ea2e748dc7cc966b4111de456de6f)`(const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & rhs)` | Operator+=s the specified RHS.
`public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator+=`](#classtask__scheduler_1_1base__thread__index_1abfcf2ca1e85eaa38cbceea06c741afce)`(int32_t rhs)` | 
`public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator-=`](#classtask__scheduler_1_1base__thread__index_1ab10303205c2cc214fdad94da83d8d136)`(const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & rhs)` | Operator-=s the specified RHS.
`public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator-=`](#classtask__scheduler_1_1base__thread__index_1a0989644943a728c4144d1547fe9c705c)`(int32_t rhs)` | Operator-=s the specified RHS.
`public inline  `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index_1aa7a5446675e0b90a8042835008441333)`(const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & other)` | Initializes a new instance of the [base_thread_index](#classtask__scheduler_1_1base__thread__index) class.
`public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator=`](#classtask__scheduler_1_1base__thread__index_1a5ae3749c9ffb66ac063f3c7b96000a01)`(const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & other)` | Operator=s the specified other.
`public inline  `[`operator const ValueType`](#classtask__scheduler_1_1base__thread__index_1a8c0df22d5de3adf670c2ad84a6926741)`()` | Implements the operator const ValueType operator.
`public inline thread_mask_int_t `[`get_mask`](#classtask__scheduler_1_1base__thread__index_1a172b73bf6ca72af10d17ff1fcb691c2c)`()` | Gets the mask.
`public inline bool `[`is_set`](#classtask__scheduler_1_1base__thread__index_1a89be8352bff54cad5537e9a50a87eee2)`(thread_mask_int_t _other_mask)` | Determines whether the specified other mask is set.

## Members

#### `public inline  `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index_1a1f4f899bdce08e5444d3fa383b75fcce)`(`[`thread_pool`](#classtask__scheduler_1_1base__thread__pool)` * _pool,ValueType _value)` 

Initializes a new instance of the [base_thread_index](#classtask__scheduler_1_1base__thread__index) class.

#### Parameters
* `_pool` The pool.

* `_value` The value.

#### `public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator++`](#classtask__scheduler_1_1base__thread__index_1a0fbb1d8170d706a76591a013a3e9cbe4)`()` 

Operator++s this instance.

#### Returns
[task_scheduler.base_thread_index](#classtask__scheduler_1_1base__thread__index)<ValueType, TMemInterface> &.

#### `public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator--`](#classtask__scheduler_1_1base__thread__index_1af4cf457a4b9aa657d41183de1164c0af)`()` 

Operators this instance.

#### Returns
[task_scheduler.base_thread_index](#classtask__scheduler_1_1base__thread__index)<ValueType, TMemInterface> &.

#### `public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator+=`](#classtask__scheduler_1_1base__thread__index_1aa40ea2e748dc7cc966b4111de456de6f)`(const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & rhs)` 

Operator+=s the specified RHS.

#### Parameters
* `rhs` The RHS.

#### Returns
[task_scheduler.base_thread_index](#classtask__scheduler_1_1base__thread__index)<ValueType, TMemInterface> &.

#### `public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator+=`](#classtask__scheduler_1_1base__thread__index_1abfcf2ca1e85eaa38cbceea06c741afce)`(int32_t rhs)` 

#### `public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator-=`](#classtask__scheduler_1_1base__thread__index_1ab10303205c2cc214fdad94da83d8d136)`(const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & rhs)` 

Operator-=s the specified RHS.

#### Parameters
* `rhs` The RHS.

#### Returns
[task_scheduler.base_thread_index](#classtask__scheduler_1_1base__thread__index)<ValueType, TMemInterface> &.

#### `public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator-=`](#classtask__scheduler_1_1base__thread__index_1a0989644943a728c4144d1547fe9c705c)`(int32_t rhs)` 

Operator-=s the specified RHS.

#### Parameters
* `rhs` The RHS.

#### Returns
[task_scheduler.base_thread_index](#classtask__scheduler_1_1base__thread__index)<ValueType, TMemInterface> &.

#### `public inline  `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index_1aa7a5446675e0b90a8042835008441333)`(const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & other)` 

Initializes a new instance of the [base_thread_index](#classtask__scheduler_1_1base__thread__index) class.

#### Parameters
* `other` The other.

#### `public inline `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & `[`operator=`](#classtask__scheduler_1_1base__thread__index_1a5ae3749c9ffb66ac063f3c7b96000a01)`(const `[`base_thread_index`](#classtask__scheduler_1_1base__thread__index)` & other)` 

Operator=s the specified other.

#### Parameters
* `other` The other.

#### Returns
[task_scheduler.base_thread_index](#classtask__scheduler_1_1base__thread__index)<ValueType, TMemInterface> &.

#### `public inline  `[`operator const ValueType`](#classtask__scheduler_1_1base__thread__index_1a8c0df22d5de3adf670c2ad84a6926741)`()` 

Implements the operator const ValueType operator.

#### Returns
The result of the operator.

#### `public inline thread_mask_int_t `[`get_mask`](#classtask__scheduler_1_1base__thread__index_1a172b73bf6ca72af10d17ff1fcb691c2c)`()` 

Gets the mask.

#### Returns
thread_mask_int_t.

#### `public inline bool `[`is_set`](#classtask__scheduler_1_1base__thread__index_1a89be8352bff54cad5537e9a50a87eee2)`(thread_mask_int_t _other_mask)` 

Determines whether the specified other mask is set.

#### Parameters
* `_other_mask` The other mask.

#### Returns
bool.

# class `task_scheduler::base_thread_pool` 

Class [base_thread_pool](#classtask__scheduler_1_1base__thread__pool).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`setup_container`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container)` `[`setup`](#classtask__scheduler_1_1base__thread__pool_1a7ca9b16609db64232f1291fc2bf00644) | The setup
`public thread_num_t `[`num_threads`](#classtask__scheduler_1_1base__thread__pool_1ad0de7c41b25bda23aaca15f60de37341) | The number threads
`public `[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` * `[`task_graph`](#classtask__scheduler_1_1base__thread__pool_1a97f410f5d7001c317876c4e8e32adb60) | The task graph
`public `[`thread_type`](#structtask__scheduler_1_1base__thread)` * `[`threads`](#classtask__scheduler_1_1base__thread__pool_1a54576f4fdd0856eb6bbe141608a473d1) | 
`public `[`task_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` `[`task_memory_allocator`](#classtask__scheduler_1_1base__thread__pool_1ad6efddd421c7bdf7333d77856e72ec37) | The threads
`public std::atomic< uint32_t > `[`num_working`](#classtask__scheduler_1_1base__thread__pool_1a5622754d5d8eb055e33837e5bfd31aa5) | The number working
`public optimization std::atomic< typename task_type::rank_type > `[`queue_rank`](#classtask__scheduler_1_1base__thread__pool_1a2c86de4be3b279ec7aaed74c072b9e1e) | 
`public  `[`base_thread_pool`](#classtask__scheduler_1_1base__thread__pool_1a9466e019b76e7a5ada8b42fd36fdc57e)`(thread_num_t _num_threads)` | Initializes a new instance of the [base_thread_pool](#classtask__scheduler_1_1base__thread__pool) class.
`public void `[`start`](#classtask__scheduler_1_1base__thread__pool_1a32aad307aec555fb560c6df5efad28c5)`(`[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & task_graph)` | Starts the specified task graph.
`public void `[`stop`](#classtask__scheduler_1_1base__thread__pool_1aff9587c6afccc5ba132df118c17e7e59)`()` | Stops this instance.
`public void `[`wake_up`](#classtask__scheduler_1_1base__thread__pool_1a26a7f4c7aa8513da887642e2f36b5026)`(thread_num_t _num_threads_to_wake_up,uint64_t _thread_affinity_mask)` | Wakes up.
`public `[`thread_type`](#structtask__scheduler_1_1base__thread)` * `[`get_current_thread`](#classtask__scheduler_1_1base__thread__pool_1a64d60e74e9e1fd8a02d5d64f8147b035)`()` | Gets the current thread.
`enum `[`state_selector`](#classtask__scheduler_1_1base__thread__pool_1ae81f4ae71df3ee8f45e5712ecde9af0e) | Enum state_selector

## Members

#### `public `[`setup_container`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container)` `[`setup`](#classtask__scheduler_1_1base__thread__pool_1a7ca9b16609db64232f1291fc2bf00644) 

The setup

#### `public thread_num_t `[`num_threads`](#classtask__scheduler_1_1base__thread__pool_1ad0de7c41b25bda23aaca15f60de37341) 

The number threads

#### `public `[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` * `[`task_graph`](#classtask__scheduler_1_1base__thread__pool_1a97f410f5d7001c317876c4e8e32adb60) 

The task graph

#### `public `[`thread_type`](#structtask__scheduler_1_1base__thread)` * `[`threads`](#classtask__scheduler_1_1base__thread__pool_1a54576f4fdd0856eb6bbe141608a473d1) 

#### `public `[`task_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` `[`task_memory_allocator`](#classtask__scheduler_1_1base__thread__pool_1ad6efddd421c7bdf7333d77856e72ec37) 

The threads

#### `public std::atomic< uint32_t > `[`num_working`](#classtask__scheduler_1_1base__thread__pool_1a5622754d5d8eb055e33837e5bfd31aa5) 

The number working

#### `public optimization std::atomic< typename task_type::rank_type > `[`queue_rank`](#classtask__scheduler_1_1base__thread__pool_1a2c86de4be3b279ec7aaed74c072b9e1e) 

#### `public  `[`base_thread_pool`](#classtask__scheduler_1_1base__thread__pool_1a9466e019b76e7a5ada8b42fd36fdc57e)`(thread_num_t _num_threads)` 

Initializes a new instance of the [base_thread_pool](#classtask__scheduler_1_1base__thread__pool) class.

#### Parameters
* `_num_threads` The number threads.

#### `public void `[`start`](#classtask__scheduler_1_1base__thread__pool_1a32aad307aec555fb560c6df5efad28c5)`(`[`task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & task_graph)` 

Starts the specified task graph.

#### Parameters
* `task_graph` The task graph.

#### `public void `[`stop`](#classtask__scheduler_1_1base__thread__pool_1aff9587c6afccc5ba132df118c17e7e59)`()` 

Stops this instance.

#### `public void `[`wake_up`](#classtask__scheduler_1_1base__thread__pool_1a26a7f4c7aa8513da887642e2f36b5026)`(thread_num_t _num_threads_to_wake_up,uint64_t _thread_affinity_mask)` 

Wakes up.

#### Parameters
* `num_threads_to_wake_up` The number threads to wake up.

#### `public `[`thread_type`](#structtask__scheduler_1_1base__thread)` * `[`get_current_thread`](#classtask__scheduler_1_1base__thread__pool_1a64d60e74e9e1fd8a02d5d64f8147b035)`()` 

Gets the current thread.

#### Returns
thread_type *.

#### `enum `[`state_selector`](#classtask__scheduler_1_1base__thread__pool_1ae81f4ae71df3ee8f45e5712ecde9af0e) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
run            | 
request_pause            | 
request_stop            | 

Enum state_selector

# class `task_scheduler::base_worker_task` 

```
class task_scheduler::base_worker_task
  : public task_scheduler::base_task< TMemInterface >
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`base_worker_task`](#classtask__scheduler_1_1base__worker__task_1abf75f5dceffb5cdebb23e35024f4b17e)`(typename `[`super::task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & _task_graph)` | Initializes a new instance of the [base_worker_task](#classtask__scheduler_1_1base__worker__task) class.
`public  `[`~base_worker_task`](#classtask__scheduler_1_1base__worker__task_1a431287137bd958daefba84f089a6b5c3)`()` | Finalizes an instance of the [base_worker_task](#classtask__scheduler_1_1base__worker__task) class.
`protected virtual bool `[`run`](#classtask__scheduler_1_1base__worker__task_1aedf9d7f248eda1e33edf5bca9ae40278)`()` | Callback to run task
`typedef `[`worker_task_type`](#classtask__scheduler_1_1base__worker__task_1ace945923a39c3b3b912911a8638ad78d) | 
`typedef `[`super`](#classtask__scheduler_1_1base__worker__task_1a765f8383abe8409d05603d5636f1cfd2) | 

## Members

#### `public  `[`base_worker_task`](#classtask__scheduler_1_1base__worker__task_1abf75f5dceffb5cdebb23e35024f4b17e)`(typename `[`super::task_graph_type`](#classtask__scheduler_1_1base__task__graph)` & _task_graph)` 

Initializes a new instance of the [base_worker_task](#classtask__scheduler_1_1base__worker__task) class.

#### Parameters
* `_task_graph` The task graph.

#### `public  `[`~base_worker_task`](#classtask__scheduler_1_1base__worker__task_1a431287137bd958daefba84f089a6b5c3)`()` 

Finalizes an instance of the [base_worker_task](#classtask__scheduler_1_1base__worker__task) class.

#### `protected virtual bool `[`run`](#classtask__scheduler_1_1base__worker__task_1aedf9d7f248eda1e33edf5bca9ae40278)`()` 

Callback to run task

#### `typedef `[`worker_task_type`](#classtask__scheduler_1_1base__worker__task_1ace945923a39c3b3b912911a8638ad78d) 

#### `typedef `[`super`](#classtask__scheduler_1_1base__worker__task_1a765f8383abe8409d05603d5636f1cfd2) 

# class `task_scheduler::constrained` 

Class constrained.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `task_scheduler::default_mem_interface` 

Class [default_mem_interface](#classtask__scheduler_1_1default__mem__interface).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void * `[`operator new`](#classtask__scheduler_1_1default__mem__interface_1aa8666f95a6e4ba3d6ed27d7ba1e9297d)`(size_t _size)` | Implements the operator new operator.
`public void * `[`operator new`](#classtask__scheduler_1_1default__mem__interface_1a4eb674415d4f9cd91f7634a4aac08b97)`(size_t _size,size_t _alignment)` | Implements the operator new operator.
`public inline void * `[`operator new[]`](#classtask__scheduler_1_1default__mem__interface_1a34c5a436e0ba8a4c5c9b2c1bdc72b703)`(size_t _size)` | Implements the operator new[] operator.
`public inline void * `[`operator new[]`](#classtask__scheduler_1_1default__mem__interface_1ae7de3e0a57db76a5f615c78443c5eb80)`(size_t _size,size_t _alignment)` | Implements the operator new[] operator.
`public void `[`operator delete`](#classtask__scheduler_1_1default__mem__interface_1a065aaa98611775f45ddd102028aa0f50)`(void * _ptr,size_t _size)` | Implements the operator delete operator.
`public inline void `[`operator delete[]`](#classtask__scheduler_1_1default__mem__interface_1afe557fdf16c3fca219b581ea948097e3)`(void * _ptr,size_t _size)` | Implements the operator delete[] operator.

## Members

#### `public inline void * `[`operator new`](#classtask__scheduler_1_1default__mem__interface_1aa8666f95a6e4ba3d6ed27d7ba1e9297d)`(size_t _size)` 

Implements the operator new operator.

#### Parameters
* `_size` The size.

#### Returns
The result of the operator.

#### `public void * `[`operator new`](#classtask__scheduler_1_1default__mem__interface_1a4eb674415d4f9cd91f7634a4aac08b97)`(size_t _size,size_t _alignment)` 

Implements the operator new operator.

#### Parameters
* `_size` The size.

* `_alignment` The alignment.

#### Returns
The result of the operator.

#### `public inline void * `[`operator new[]`](#classtask__scheduler_1_1default__mem__interface_1a34c5a436e0ba8a4c5c9b2c1bdc72b703)`(size_t _size)` 

Implements the operator new[] operator.

#### Parameters
* `_size` The size.

#### Returns
The result of the operator.

#### `public inline void * `[`operator new[]`](#classtask__scheduler_1_1default__mem__interface_1ae7de3e0a57db76a5f615c78443c5eb80)`(size_t _size,size_t _alignment)` 

Implements the operator new[] operator.

#### Parameters
* `_size` The size.

* `_alignment` The alignment.

#### Returns
The result of the operator.

#### `public void `[`operator delete`](#classtask__scheduler_1_1default__mem__interface_1a065aaa98611775f45ddd102028aa0f50)`(void * _ptr,size_t _size)` 

Implements the operator delete operator.

#### Parameters
* `_ptr` The PTR.

* `_size` The size.

#### Returns
The result of the operator.

#### `public inline void `[`operator delete[]`](#classtask__scheduler_1_1default__mem__interface_1afe557fdf16c3fca219b581ea948097e3)`(void * _ptr,size_t _size)` 

Implements the operator delete[] operator.

#### Parameters
* `_ptr` The PTR.

* `_size` The size.

#### Returns
The result of the operator.

# class `task_scheduler::dummy` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `task_scheduler::event` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void `[`signal`](#classtask__scheduler_1_1event_1a2137f4d402a87aa7965bd4e5a44d49f1)`()` | 
`public inline void `[`wait`](#classtask__scheduler_1_1event_1af74e695c7e10ead83a00b255c7e19959)`()` | 
`protected std::mutex `[`lock`](#classtask__scheduler_1_1event_1a480277cfc41a935633b10ba8cbf1da8f) | The signal
`protected std::condition_variable `[`cond_var`](#classtask__scheduler_1_1event_1a11cb0098138e837d18c16ebd4ebf433a) | The radio

## Members

#### `public inline void `[`signal`](#classtask__scheduler_1_1event_1a2137f4d402a87aa7965bd4e5a44d49f1)`()` 

#### `public inline void `[`wait`](#classtask__scheduler_1_1event_1af74e695c7e10ead83a00b255c7e19959)`()` 

#### `protected std::mutex `[`lock`](#classtask__scheduler_1_1event_1a480277cfc41a935633b10ba8cbf1da8f) 

The signal

#### `protected std::condition_variable `[`cond_var`](#classtask__scheduler_1_1event_1a11cb0098138e837d18c16ebd4ebf433a) 

The radio

# class `task_scheduler::globals` 

class globals

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::mutex `[`io_mutex`](#classtask__scheduler_1_1globals_1aca32d712ff57206682aa74cc158ed43b) | The io mutex
`public std::atomic< thread_num_t > `[`next_thread_number`](#classtask__scheduler_1_1globals_1aa34764784c945211b69858f31706d600) | The next thread number
`public  `[`ts_windows_only`](#classtask__scheduler_1_1globals_1a2deed30e703c8002dd6417580566428d)`(HANDLE console_handle;)` | 
`public inline  `[`globals`](#classtask__scheduler_1_1globals_1a2b6bab891aeaf2d06bf0137bd84d3584)`()` | Statics the data t.

## Members

#### `public std::mutex `[`io_mutex`](#classtask__scheduler_1_1globals_1aca32d712ff57206682aa74cc158ed43b) 

The io mutex

#### `public std::atomic< thread_num_t > `[`next_thread_number`](#classtask__scheduler_1_1globals_1aa34764784c945211b69858f31706d600) 

The next thread number

#### `public  `[`ts_windows_only`](#classtask__scheduler_1_1globals_1a2deed30e703c8002dd6417580566428d)`(HANDLE console_handle;)` 

#### `public inline  `[`globals`](#classtask__scheduler_1_1globals_1a2b6bab891aeaf2d06bf0137bd84d3584)`()` 

Statics the data t.

#### Returns
int.

# class `task_scheduler::guarded` 

```
class task_scheduler::guarded
  : private TDataStructure
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`guarded`](#classtask__scheduler_1_1guarded_1a853e332a5dd464ef43c8edc1790b6d9e)`(size_t _fixed_size)` | 
`public T & `[`operator[]`](#classtask__scheduler_1_1guarded_1aa38d125f416cc030c6b27a3dcee00413)`(size_t _index)` | 
`public T & `[`at`](#classtask__scheduler_1_1guarded_1a8fc58182c63580ba02a3461a0cd39380)`(size_t _index)` | 
`public T & `[`front`](#classtask__scheduler_1_1guarded_1acaf6bd5048c86d63f22beadb8f8b979c)`()` | 
`public T & `[`back`](#classtask__scheduler_1_1guarded_1a2f66ebd548e0fc5b58d375fa8050e892)`()` | 
`public void `[`push_back`](#classtask__scheduler_1_1guarded_1a66c97756425aacf594998ae5fea001fc)`(const T & _new_item)` | 
`public void `[`clear`](#classtask__scheduler_1_1guarded_1a183ecf6dcba6f485070ec93d5416bdc0)`()` | 
`public TDataStructure::size_type `[`size`](#classtask__scheduler_1_1guarded_1a21374f36cffb101eac20e06bc0228b24)`() const` | 
`public bool `[`is_locked`](#classtask__scheduler_1_1guarded_1ac9f573a19c36dd58fd2e6b3e96e166f3)`()` | 

## Members

#### `public  `[`guarded`](#classtask__scheduler_1_1guarded_1a853e332a5dd464ef43c8edc1790b6d9e)`(size_t _fixed_size)` 

#### `public T & `[`operator[]`](#classtask__scheduler_1_1guarded_1aa38d125f416cc030c6b27a3dcee00413)`(size_t _index)` 

#### `public T & `[`at`](#classtask__scheduler_1_1guarded_1a8fc58182c63580ba02a3461a0cd39380)`(size_t _index)` 

#### `public T & `[`front`](#classtask__scheduler_1_1guarded_1acaf6bd5048c86d63f22beadb8f8b979c)`()` 

#### `public T & `[`back`](#classtask__scheduler_1_1guarded_1a2f66ebd548e0fc5b58d375fa8050e892)`()` 

#### `public void `[`push_back`](#classtask__scheduler_1_1guarded_1a66c97756425aacf594998ae5fea001fc)`(const T & _new_item)` 

#### `public void `[`clear`](#classtask__scheduler_1_1guarded_1a183ecf6dcba6f485070ec93d5416bdc0)`()` 

#### `public TDataStructure::size_type `[`size`](#classtask__scheduler_1_1guarded_1a21374f36cffb101eac20e06bc0228b24)`() const` 

#### `public bool `[`is_locked`](#classtask__scheduler_1_1guarded_1ac9f573a19c36dd58fd2e6b3e96e166f3)`()` 

# class `task_scheduler::guarded_write_array` 

```
class task_scheduler::guarded_write_array
  : public TMemInterface
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`guarded_write_array`](#classtask__scheduler_1_1guarded__write__array_1ac1d8e5930ac8e487471bba111cf4fb46)`(size_t _reserverd_size,bool _optimize_for_cache_line_size)` | Initializes a new instance of the [guarded_write_array](#classtask__scheduler_1_1guarded__write__array) class.
`public inline  `[`guarded_write_array`](#classtask__scheduler_1_1guarded__write__array_1acea2f452e3f86d57e1eb623f4f6db1f8)`(T * _existing_array,size_t _existing_array_size)` | Initializes a new instance of the [guarded_write_array](#classtask__scheduler_1_1guarded__write__array) class.
`public inline  `[`~guarded_write_array`](#classtask__scheduler_1_1guarded__write__array_1acc1cbd163bb89ebccf31b50edc21041a)`()` | Finalizes an instance of the [guarded_write_array](#classtask__scheduler_1_1guarded__write__array) class.
`public inline size_t `[`size`](#classtask__scheduler_1_1guarded__write__array_1a3c032a58845f2a4a7febba3fc4e3f33a)`()` | Sizes this instance.
`public inline size_t `[`reserved`](#classtask__scheduler_1_1guarded__write__array_1a64030f3555a7ac9791d7c5397aed5505)`()` | Reserveds this instance.
`public T * `[`operator &`](#classtask__scheduler_1_1guarded__write__array_1ace7c9b5c93246fb3d7ef09da7b69c139)`()` | Operator&s this instance.
`public inline void `[`push_back`](#classtask__scheduler_1_1guarded__write__array_1aeabb75b18de1d0321b5907c4d773817f)`(const T & _new_item)` | Pushes the back.
`public inline void `[`clear`](#classtask__scheduler_1_1guarded__write__array_1a69f1bdfba4a47a05765c207cfaa17e80)`()` | Clears this instance.
`public inline T & `[`operator[]`](#classtask__scheduler_1_1guarded__write__array_1a07dd1105360e6fa07e604b075a3d952a)`(size_t _index)` | Operator[]s the specified index.

## Members

#### `public inline  `[`guarded_write_array`](#classtask__scheduler_1_1guarded__write__array_1ac1d8e5930ac8e487471bba111cf4fb46)`(size_t _reserverd_size,bool _optimize_for_cache_line_size)` 

Initializes a new instance of the [guarded_write_array](#classtask__scheduler_1_1guarded__write__array) class.

#### Parameters
* `_reserved_size` Size of the reserved.

* `_optimize_for_cache_line_size` Size of the optimize for cache line.

#### `public inline  `[`guarded_write_array`](#classtask__scheduler_1_1guarded__write__array_1acea2f452e3f86d57e1eb623f4f6db1f8)`(T * _existing_array,size_t _existing_array_size)` 

Initializes a new instance of the [guarded_write_array](#classtask__scheduler_1_1guarded__write__array) class.

#### Parameters
* `_existing_array` The existing array.

* `_existing_array_size` Size of the existing array.

#### `public inline  `[`~guarded_write_array`](#classtask__scheduler_1_1guarded__write__array_1acc1cbd163bb89ebccf31b50edc21041a)`()` 

Finalizes an instance of the [guarded_write_array](#classtask__scheduler_1_1guarded__write__array) class.

#### `public inline size_t `[`size`](#classtask__scheduler_1_1guarded__write__array_1a3c032a58845f2a4a7febba3fc4e3f33a)`()` 

Sizes this instance.

#### Returns
size_t.

#### `public inline size_t `[`reserved`](#classtask__scheduler_1_1guarded__write__array_1a64030f3555a7ac9791d7c5397aed5505)`()` 

Reserveds this instance.

#### Returns
size_t.

#### `public T * `[`operator &`](#classtask__scheduler_1_1guarded__write__array_1ace7c9b5c93246fb3d7ef09da7b69c139)`()` 

Operator&s this instance.

#### Returns
T *.

#### `public inline void `[`push_back`](#classtask__scheduler_1_1guarded__write__array_1aeabb75b18de1d0321b5907c4d773817f)`(const T & _new_item)` 

Pushes the back.

#### Parameters
* `_new_item` The new item.

#### `public inline void `[`clear`](#classtask__scheduler_1_1guarded__write__array_1a69f1bdfba4a47a05765c207cfaa17e80)`()` 

Clears this instance.

#### `public inline T & `[`operator[]`](#classtask__scheduler_1_1guarded__write__array_1a07dd1105360e6fa07e604b075a3d952a)`(size_t _index)` 

Operator[]s the specified index.

#### Parameters
* `_index` The index.

#### Returns
T &.

# class `task_scheduler::lock_free_batch_dispatcher` 

```
class task_scheduler::lock_free_batch_dispatcher
  : public TMemInterface
```  

Class [lock_free_batch_dispatcher](#classtask__scheduler_1_1lock__free__batch__dispatcher).

**See also**: TMemInterface

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`lock_free_batch_dispatcher`](#classtask__scheduler_1_1lock__free__batch__dispatcher_1a41deff0e3b227f5ac1131d38f8b3e614)`(TDataType & _data_type)` | Initializes a new instance of the [lock_free_batch_dispatcher](#classtask__scheduler_1_1lock__free__batch__dispatcher) class.
`public  `[`~lock_free_batch_dispatcher`](#classtask__scheduler_1_1lock__free__batch__dispatcher_1a77851bd98d07900d18df6b4991c522b7)`()` | Finalizes an instance of the [lock_free_batch_dispatcher](#classtask__scheduler_1_1lock__free__batch__dispatcher) class.
`public T * `[`get_next_batch`](#classtask__scheduler_1_1lock__free__batch__dispatcher_1a3ebb1f2049d5d0c263abbe641c7cbb8b)`(size_t _requested_batch_size,size_t & _returned_batch_size)` | Gets the next batch.

## Members

#### `public  `[`lock_free_batch_dispatcher`](#classtask__scheduler_1_1lock__free__batch__dispatcher_1a41deff0e3b227f5ac1131d38f8b3e614)`(TDataType & _data_type)` 

Initializes a new instance of the [lock_free_batch_dispatcher](#classtask__scheduler_1_1lock__free__batch__dispatcher) class.

#### Parameters
* `_data_type` Type of the data.

#### `public  `[`~lock_free_batch_dispatcher`](#classtask__scheduler_1_1lock__free__batch__dispatcher_1a77851bd98d07900d18df6b4991c522b7)`()` 

Finalizes an instance of the [lock_free_batch_dispatcher](#classtask__scheduler_1_1lock__free__batch__dispatcher) class.

#### `public T * `[`get_next_batch`](#classtask__scheduler_1_1lock__free__batch__dispatcher_1a3ebb1f2049d5d0c263abbe641c7cbb8b)`(size_t _requested_batch_size,size_t & _returned_batch_size)` 

Gets the next batch.

#### Parameters
* `_requested_batch_size` Size of the requested batch.

* `_returned_batch_size` Size of the returned batch.

#### Returns
T *.

# class `task_scheduler::lock_free_node_dispenser` 

```
class task_scheduler::lock_free_node_dispenser
  : public TMemInterface
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`lock_free_node_dispenser`](#classtask__scheduler_1_1lock__free__node__dispenser_1adecc41b77b29fe45aa315bda0237400d)`(uint32_t _start_count)` | 
`public inline  `[`~lock_free_node_dispenser`](#classtask__scheduler_1_1lock__free__node__dispenser_1aca72bf88f52e96c0b2f3343793cde5b5)`()` | 
`public inline `[`node_type`](#structtask__scheduler_1_1lock__free__node)` * `[`new_node`](#classtask__scheduler_1_1lock__free__node__dispenser_1a705a5f02d3408805f9ba9df0b855603a)`()` | 
`public inline void `[`free_node`](#classtask__scheduler_1_1lock__free__node__dispenser_1a1c784c1489e6e02b092e978b7adfab92)`(`[`node_type`](#structtask__scheduler_1_1lock__free__node)` * _node)` | 

## Members

#### `public inline  `[`lock_free_node_dispenser`](#classtask__scheduler_1_1lock__free__node__dispenser_1adecc41b77b29fe45aa315bda0237400d)`(uint32_t _start_count)` 

#### `public inline  `[`~lock_free_node_dispenser`](#classtask__scheduler_1_1lock__free__node__dispenser_1aca72bf88f52e96c0b2f3343793cde5b5)`()` 

#### `public inline `[`node_type`](#structtask__scheduler_1_1lock__free__node)` * `[`new_node`](#classtask__scheduler_1_1lock__free__node__dispenser_1a705a5f02d3408805f9ba9df0b855603a)`()` 

#### `public inline void `[`free_node`](#classtask__scheduler_1_1lock__free__node__dispenser_1a1c784c1489e6e02b092e978b7adfab92)`(`[`node_type`](#structtask__scheduler_1_1lock__free__node)` * _node)` 

# class `task_scheduler::lock_free_node_stack` 

```
class task_scheduler::lock_free_node_stack
  : public TMemInterface
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`lock_free_node_stack`](#classtask__scheduler_1_1lock__free__node__stack_1af26b8e2ceb4922ac6398658ce72947a0)`()` | 
`public inline void `[`push_front`](#classtask__scheduler_1_1lock__free__node__stack_1a5a3d5fc11d1ac38be23c8276a457a2f2)`(`[`node_type`](#structtask__scheduler_1_1lock__free__node)` * _node)` | 
`public inline `[`node_type`](#structtask__scheduler_1_1lock__free__node)` * `[`pop_front`](#classtask__scheduler_1_1lock__free__node__stack_1a4cc63553fcc4bdfffda0bc7933839eef)`()` | 
`public inline bool `[`empty`](#classtask__scheduler_1_1lock__free__node__stack_1acfc159aaa328ff5f0e85afe71643c061)`()` | 
`public inline  `[`~lock_free_node_stack`](#classtask__scheduler_1_1lock__free__node__stack_1a4cb7a1cee83b2e470aecdfd66047f2ff)`()` | 

## Members

#### `public inline  `[`lock_free_node_stack`](#classtask__scheduler_1_1lock__free__node__stack_1af26b8e2ceb4922ac6398658ce72947a0)`()` 

#### `public inline void `[`push_front`](#classtask__scheduler_1_1lock__free__node__stack_1a5a3d5fc11d1ac38be23c8276a457a2f2)`(`[`node_type`](#structtask__scheduler_1_1lock__free__node)` * _node)` 

#### `public inline `[`node_type`](#structtask__scheduler_1_1lock__free__node)` * `[`pop_front`](#classtask__scheduler_1_1lock__free__node__stack_1a4cc63553fcc4bdfffda0bc7933839eef)`()` 

#### `public inline bool `[`empty`](#classtask__scheduler_1_1lock__free__node__stack_1acfc159aaa328ff5f0e85afe71643c061)`()` 

#### `public inline  `[`~lock_free_node_stack`](#classtask__scheduler_1_1lock__free__node__stack_1a4cb7a1cee83b2e470aecdfd66047f2ff)`()` 

# class `task_scheduler::lock_free_queue` 

```
class task_scheduler::lock_free_queue
  : public TMemInterface
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public TPolicy `[`queue`](#classtask__scheduler_1_1lock__free__queue_1a494fada23ccb9f6c7897389d10540f07) | 
`public inline  `[`lock_free_queue`](#classtask__scheduler_1_1lock__free__queue_1a506cfd65d19bd49f3bb548ff514dac4f)`()` | 
`public inline  `[`lock_free_queue`](#classtask__scheduler_1_1lock__free__queue_1abf4a746b5feb80b18de1cef712c723fb)`(TParam param)` | 
`public inline virtual bool `[`push_back`](#classtask__scheduler_1_1lock__free__queue_1a2f38852510b38a6ab7ecd0e93938bb4a)`(T newData)` | 
`public inline virtual bool `[`pop_front`](#classtask__scheduler_1_1lock__free__queue_1aacdb6e87f7e3435bc2405ba86b93985c)`(T & val)` | 
`public inline virtual bool `[`pop_back`](#classtask__scheduler_1_1lock__free__queue_1a249b555664926baae4dd8ff52a5eb029)`(T & val)` | 
`public inline virtual bool `[`empty`](#classtask__scheduler_1_1lock__free__queue_1a0760717988d6b0792d355bc8562ce491)`() const` | 
`public inline virtual  `[`~lock_free_queue`](#classtask__scheduler_1_1lock__free__queue_1af8ae98180f9480ddbcf6a9abc799bdcd)`()` | 

## Members

#### `public TPolicy `[`queue`](#classtask__scheduler_1_1lock__free__queue_1a494fada23ccb9f6c7897389d10540f07) 

#### `public inline  `[`lock_free_queue`](#classtask__scheduler_1_1lock__free__queue_1a506cfd65d19bd49f3bb548ff514dac4f)`()` 

#### `public inline  `[`lock_free_queue`](#classtask__scheduler_1_1lock__free__queue_1abf4a746b5feb80b18de1cef712c723fb)`(TParam param)` 

#### `public inline virtual bool `[`push_back`](#classtask__scheduler_1_1lock__free__queue_1a2f38852510b38a6ab7ecd0e93938bb4a)`(T newData)` 

#### `public inline virtual bool `[`pop_front`](#classtask__scheduler_1_1lock__free__queue_1aacdb6e87f7e3435bc2405ba86b93985c)`(T & val)` 

#### `public inline virtual bool `[`pop_back`](#classtask__scheduler_1_1lock__free__queue_1a249b555664926baae4dd8ff52a5eb029)`(T & val)` 

#### `public inline virtual bool `[`empty`](#classtask__scheduler_1_1lock__free__queue_1a0760717988d6b0792d355bc8562ce491)`() const` 

#### `public inline virtual  `[`~lock_free_queue`](#classtask__scheduler_1_1lock__free__queue_1af8ae98180f9480ddbcf6a9abc799bdcd)`()` 

# class `task_scheduler::lock_free_stack` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`lock_free_stack`](#classtask__scheduler_1_1lock__free__stack_1a46b6f0d1383a0036eede67ab5b2acf7d)`(TDispenser * _dispenser)` | 
`public inline  `[`~lock_free_stack`](#classtask__scheduler_1_1lock__free__stack_1ade16fb9f0459afbde9581a0f26bcaf69)`()` | 
`public inline void `[`push_front`](#classtask__scheduler_1_1lock__free__stack_1a04d3fc5786bf04f851abe849cfff8f98)`(const T & _value)` | 
`public bool `[`pop_front`](#classtask__scheduler_1_1lock__free__stack_1ab4ff98c63792a54aa9b2497c011a97a4)`(T & _out)` | 
`public inline bool `[`empty`](#classtask__scheduler_1_1lock__free__stack_1a6a0ebc0f42a0a1770499b8fc68bef37f)`()` | 

## Members

#### `public inline  `[`lock_free_stack`](#classtask__scheduler_1_1lock__free__stack_1a46b6f0d1383a0036eede67ab5b2acf7d)`(TDispenser * _dispenser)` 

#### `public inline  `[`~lock_free_stack`](#classtask__scheduler_1_1lock__free__stack_1ade16fb9f0459afbde9581a0f26bcaf69)`()` 

#### `public inline void `[`push_front`](#classtask__scheduler_1_1lock__free__stack_1a04d3fc5786bf04f851abe849cfff8f98)`(const T & _value)` 

#### `public bool `[`pop_front`](#classtask__scheduler_1_1lock__free__stack_1ab4ff98c63792a54aa9b2497c011a97a4)`(T & _out)` 

#### `public inline bool `[`empty`](#classtask__scheduler_1_1lock__free__stack_1a6a0ebc0f42a0a1770499b8fc68bef37f)`()` 

# class `task_scheduler::multi_producer_multi_consumer` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`multi_producer_multi_consumer`](#classtask__scheduler_1_1multi__producer__multi__consumer_1a86f3ea14f76a1329493a4a3897009d20)`(TDispenser * _dispenser)` | 
`public inline  `[`~multi_producer_multi_consumer`](#classtask__scheduler_1_1multi__producer__multi__consumer_1ab9309914af6896d59b2f3de8630b7bd5)`()` | 
`public inline bool `[`push_back`](#classtask__scheduler_1_1multi__producer__multi__consumer_1afc3fb91d0800ebe5090b49dfc974f32d)`(const T & _value)` | Add an object in the queue 
`public inline bool `[`peek`](#classtask__scheduler_1_1multi__producer__multi__consumer_1a7fcb25b94967b7b390589535a727b73e)`(T & _out)` | 
`public inline bool `[`pop_front`](#classtask__scheduler_1_1multi__producer__multi__consumer_1af652da3f7eb6fd36c7bcaa1c6b29d978)`(T & _out)` | 
`public inline bool `[`empty`](#classtask__scheduler_1_1multi__producer__multi__consumer_1a57032a6767142f5291be7bbe0dbbc59a)`() const` | 
`public inline void `[`clear`](#classtask__scheduler_1_1multi__producer__multi__consumer_1ac76c2290ddea6abb1eae41b61a240f6d)`()` | 

## Members

#### `public inline  `[`multi_producer_multi_consumer`](#classtask__scheduler_1_1multi__producer__multi__consumer_1a86f3ea14f76a1329493a4a3897009d20)`(TDispenser * _dispenser)` 

#### `public inline  `[`~multi_producer_multi_consumer`](#classtask__scheduler_1_1multi__producer__multi__consumer_1ab9309914af6896d59b2f3de8630b7bd5)`()` 

#### `public inline bool `[`push_back`](#classtask__scheduler_1_1multi__producer__multi__consumer_1afc3fb91d0800ebe5090b49dfc974f32d)`(const T & _value)` 

Add an object in the queue 
#### Parameters
* `_value` Object to add

#### `public inline bool `[`peek`](#classtask__scheduler_1_1multi__producer__multi__consumer_1a7fcb25b94967b7b390589535a727b73e)`(T & _out)` 

#### `public inline bool `[`pop_front`](#classtask__scheduler_1_1multi__producer__multi__consumer_1af652da3f7eb6fd36c7bcaa1c6b29d978)`(T & _out)` 

#### `public inline bool `[`empty`](#classtask__scheduler_1_1multi__producer__multi__consumer_1a57032a6767142f5291be7bbe0dbbc59a)`() const` 

#### `public inline void `[`clear`](#classtask__scheduler_1_1multi__producer__multi__consumer_1ac76c2290ddea6abb1eae41b61a240f6d)`()` 

# class `task_scheduler::scoped_enter_exit` 

Class [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit).

**See also**: T

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_1a643f3506f224f2da7571cf0177c59a73)`(TParam & _param)` | Initializes a new instance of the [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit) class.
`public inline  `[`scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_1af3dcf58181a1bbfaa8126b1b8f39e055)`(TParam && _param)` | 
`public inline  `[`~scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_1ab842b433fe11645a18ec94eabe4cbb24)`()` | Finalizes an instance of the [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit) class.

## Members

#### `public inline  `[`scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_1a643f3506f224f2da7571cf0177c59a73)`(TParam & _param)` 

Initializes a new instance of the [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit) class.

#### Parameters
* `_param` The parameter.

#### `public inline  `[`scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_1af3dcf58181a1bbfaa8126b1b8f39e055)`(TParam && _param)` 

#### `public inline  `[`~scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_1ab842b433fe11645a18ec94eabe4cbb24)`()` 

Finalizes an instance of the [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit) class.

# class `task_scheduler::scoped_enter_exit< TClassType, base_scoped_param >` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_3_01TClassType_00_01base__scoped__param_01_4_1a2ba6c7be2a89723faf33eb4077f17a39)`()` | Initializes a new instance of the [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit) class.
`public inline  `[`~scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_3_01TClassType_00_01base__scoped__param_01_4_1a643957528f63ff7f29e65c67a1f8834a)`()` | Finalizes an instance of the [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit) class.

## Members

#### `public inline  `[`scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_3_01TClassType_00_01base__scoped__param_01_4_1a2ba6c7be2a89723faf33eb4077f17a39)`()` 

Initializes a new instance of the [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit) class.

#### `public inline  `[`~scoped_enter_exit`](#classtask__scheduler_1_1scoped__enter__exit_3_01TClassType_00_01base__scoped__param_01_4_1a643957528f63ff7f29e65c67a1f8834a)`()` 

Finalizes an instance of the [scoped_enter_exit](#classtask__scheduler_1_1scoped__enter__exit) class.

# class `task_scheduler::stl_allocator` 

```
class task_scheduler::stl_allocator
  : public TMemInterface
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`stl_allocator`](#classtask__scheduler_1_1stl__allocator_1a7e115582fac7b0443a67b0a793a5bdf1)`()` | Initializes a new instance of the [stl_allocator](#classtask__scheduler_1_1stl__allocator) class.
`public inline  `[`~stl_allocator`](#classtask__scheduler_1_1stl__allocator_1a9705cb992d455569ac723028b53ddf3a)`()` | Finalizes an instance of the [stl_allocator](#classtask__scheduler_1_1stl__allocator) class.
`public inline  `[`stl_allocator`](#classtask__scheduler_1_1stl__allocator_1afbbd4199fea96040a48856cfd6efe0b3)`(`[`stl_allocator`](#classtask__scheduler_1_1stl__allocator)` const &)` | Initializes a new instance of the [stl_allocator](#classtask__scheduler_1_1stl__allocator) class.
`public template<>`  <br/>`inline  `[`stl_allocator`](#classtask__scheduler_1_1stl__allocator_1a0d8cc9f4ee3977220f7d7222be623605)`(`[`stl_allocator`](#classtask__scheduler_1_1stl__allocator)`< U, TMemInterface > const &)` | Initializes a new instance of the [stl_allocator](#classtask__scheduler_1_1stl__allocator) class.
`public inline pointer `[`address`](#classtask__scheduler_1_1stl__allocator_1aeade0313ce45ab610387384dfbaa1b5f)`(reference r)` | Addresses the specified r.
`public inline const_pointer `[`address`](#classtask__scheduler_1_1stl__allocator_1a1ca26a4007745387dc7a840edd156e15)`(const_reference r)` | Addresses the specified r.
`public inline pointer `[`allocate`](#classtask__scheduler_1_1stl__allocator_1a373dcde8fb451e87662d705aa3978be7)`(size_type _cnt,typename std::allocator< void >::const_pointer)` | Allocates the specified count.
`public inline void `[`deallocate`](#classtask__scheduler_1_1stl__allocator_1acfa566ae24db023efa69f8d25005820a)`(pointer _p,size_type _n)` | Deallocates the specified p.
`public inline size_type `[`max_size`](#classtask__scheduler_1_1stl__allocator_1a66d75f3adc5a26ea762403974e92c021)`() const` | Maximums the size.
`public inline bool `[`operator==`](#classtask__scheduler_1_1stl__allocator_1a80dd96e767167d8a0daa30eec0a6f65d)`(`[`stl_allocator`](#classtask__scheduler_1_1stl__allocator)` const &) const` | Operator==s the specified .
`public inline bool `[`operator!=`](#classtask__scheduler_1_1stl__allocator_1a726969f91cdfeec001313b5039ff6bd8)`(`[`stl_allocator`](#classtask__scheduler_1_1stl__allocator)` const & _a)` | Operator!=s the specified a.
`typedef `[`value_type`](#classtask__scheduler_1_1stl__allocator_1a3856065f1cccf5d4b89249a41a9a6d2b) | 
`typedef `[`pointer`](#classtask__scheduler_1_1stl__allocator_1abdfad6df188e58ce025883b94c48176b) | 
`typedef `[`const_pointer`](#classtask__scheduler_1_1stl__allocator_1a65240dd6091e48b8b3c6258e2cc254ce) | 
`typedef `[`reference`](#classtask__scheduler_1_1stl__allocator_1a558ad5809251ed7466ee619140e728fc) | 
`typedef `[`const_reference`](#classtask__scheduler_1_1stl__allocator_1acce5d59931c8253362efb73ff2cebfd9) | 
`typedef `[`size_type`](#classtask__scheduler_1_1stl__allocator_1a49d5f9c51e7b9fe3742bafbcdb579fd6) | 
`typedef `[`difference_type`](#classtask__scheduler_1_1stl__allocator_1a4bd4222d49a6f112e2d6727ce6c35475) | 

## Members

#### `public inline  `[`stl_allocator`](#classtask__scheduler_1_1stl__allocator_1a7e115582fac7b0443a67b0a793a5bdf1)`()` 

Initializes a new instance of the [stl_allocator](#classtask__scheduler_1_1stl__allocator) class.

#### `public inline  `[`~stl_allocator`](#classtask__scheduler_1_1stl__allocator_1a9705cb992d455569ac723028b53ddf3a)`()` 

Finalizes an instance of the [stl_allocator](#classtask__scheduler_1_1stl__allocator) class.

#### `public inline  `[`stl_allocator`](#classtask__scheduler_1_1stl__allocator_1afbbd4199fea96040a48856cfd6efe0b3)`(`[`stl_allocator`](#classtask__scheduler_1_1stl__allocator)` const &)` 

Initializes a new instance of the [stl_allocator](#classtask__scheduler_1_1stl__allocator) class.

The .

#### `public template<>`  <br/>`inline  `[`stl_allocator`](#classtask__scheduler_1_1stl__allocator_1a0d8cc9f4ee3977220f7d7222be623605)`(`[`stl_allocator`](#classtask__scheduler_1_1stl__allocator)`< U, TMemInterface > const &)` 

Initializes a new instance of the [stl_allocator](#classtask__scheduler_1_1stl__allocator) class.

The .

#### `public inline pointer `[`address`](#classtask__scheduler_1_1stl__allocator_1aeade0313ce45ab610387384dfbaa1b5f)`(reference r)` 

Addresses the specified r.

#### Parameters
* `r` The r.

#### Returns
pointer.

#### `public inline const_pointer `[`address`](#classtask__scheduler_1_1stl__allocator_1a1ca26a4007745387dc7a840edd156e15)`(const_reference r)` 

Addresses the specified r.

#### Parameters
* `r` The r.

#### Returns
const_pointer.

#### `public inline pointer `[`allocate`](#classtask__scheduler_1_1stl__allocator_1a373dcde8fb451e87662d705aa3978be7)`(size_type _cnt,typename std::allocator< void >::const_pointer)` 

Allocates the specified count.

#### Parameters
* `_cnt` The count.

The .

#### Returns
pointer.

#### `public inline void `[`deallocate`](#classtask__scheduler_1_1stl__allocator_1acfa566ae24db023efa69f8d25005820a)`(pointer _p,size_type _n)` 

Deallocates the specified p.

#### Parameters
* `_p` The p.

* `_n` The n.

#### `public inline size_type `[`max_size`](#classtask__scheduler_1_1stl__allocator_1a66d75f3adc5a26ea762403974e92c021)`() const` 

Maximums the size.

#### Returns
size_type.

#### `public inline bool `[`operator==`](#classtask__scheduler_1_1stl__allocator_1a80dd96e767167d8a0daa30eec0a6f65d)`(`[`stl_allocator`](#classtask__scheduler_1_1stl__allocator)` const &) const` 

Operator==s the specified .

The .

#### Returns
bool.

#### `public inline bool `[`operator!=`](#classtask__scheduler_1_1stl__allocator_1a726969f91cdfeec001313b5039ff6bd8)`(`[`stl_allocator`](#classtask__scheduler_1_1stl__allocator)` const & _a)` 

Operator!=s the specified a.

#### Parameters
* `_a` a.

#### Returns
bool.

#### `typedef `[`value_type`](#classtask__scheduler_1_1stl__allocator_1a3856065f1cccf5d4b89249a41a9a6d2b) 

#### `typedef `[`pointer`](#classtask__scheduler_1_1stl__allocator_1abdfad6df188e58ce025883b94c48176b) 

#### `typedef `[`const_pointer`](#classtask__scheduler_1_1stl__allocator_1a65240dd6091e48b8b3c6258e2cc254ce) 

#### `typedef `[`reference`](#classtask__scheduler_1_1stl__allocator_1a558ad5809251ed7466ee619140e728fc) 

#### `typedef `[`const_reference`](#classtask__scheduler_1_1stl__allocator_1acce5d59931c8253362efb73ff2cebfd9) 

#### `typedef `[`size_type`](#classtask__scheduler_1_1stl__allocator_1a49d5f9c51e7b9fe3742bafbcdb579fd6) 

#### `typedef `[`difference_type`](#classtask__scheduler_1_1stl__allocator_1a4bd4222d49a6f112e2d6727ce6c35475) 

# class `task_scheduler::unsafe_multi_threaded_access_detector` 

Class [unsafe_multi_threaded_access_detector](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`unsafe_multi_threaded_access_detector`](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector_1a0d713e0d7892a7f9ba6c1701a133c389)`()` | Initializes a new instance of the [unsafe_multi_threaded_access_detector](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector) class.
`public inline bool `[`enter`](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector_1a3b3910f1b9391d109cce5e5550450b1d)`(TClassType & storage)` | Enters the specified storage.
`public inline bool `[`exit`](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector_1aea6901e9e52d0f9dd908687f1231b1a1)`(TClassType & storage)` | Exits the specified storage.

## Members

#### `public inline  `[`unsafe_multi_threaded_access_detector`](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector_1a0d713e0d7892a7f9ba6c1701a133c389)`()` 

Initializes a new instance of the [unsafe_multi_threaded_access_detector](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector) class.

#### `public inline bool `[`enter`](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector_1a3b3910f1b9391d109cce5e5550450b1d)`(TClassType & storage)` 

Enters the specified storage.

#### Parameters
* `storage` The storage.

#### Returns
bool.

#### `public inline bool `[`exit`](#classtask__scheduler_1_1unsafe__multi__threaded__access__detector_1aea6901e9e52d0f9dd908687f1231b1a1)`(TClassType & storage)` 

Exits the specified storage.

#### Parameters
* `storage` The storage.

#### Returns
bool.

# struct `task_scheduler::atomic_lock_free_node` 

```
struct task_scheduler::atomic_lock_free_node
  : public TMemInterface
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`node_type`](#structtask__scheduler_1_1lock__free__node)` *volatile `[`node`](#structtask__scheduler_1_1atomic__lock__free__node_1a8256b56afb7801942643913db0979820) | 
`public atomics::type `[`as_atomic`](#structtask__scheduler_1_1atomic__lock__free__node_1af19b9a100255a1147daaee0f1a70e519) | 
`public union task_scheduler::atomic_lock_free_node::@0 `[`@1`](#structtask__scheduler_1_1atomic__lock__free__node_1a3a90426cd3ddbe8b41768fa95208c1ac) | 
`typedef `[`node_type`](#structtask__scheduler_1_1atomic__lock__free__node_1a20eeeada550deb5546bdcbbb471216f4) | 

## Members

#### `public `[`node_type`](#structtask__scheduler_1_1lock__free__node)` *volatile `[`node`](#structtask__scheduler_1_1atomic__lock__free__node_1a8256b56afb7801942643913db0979820) 

#### `public atomics::type `[`as_atomic`](#structtask__scheduler_1_1atomic__lock__free__node_1af19b9a100255a1147daaee0f1a70e519) 

#### `public union task_scheduler::atomic_lock_free_node::@0 `[`@1`](#structtask__scheduler_1_1atomic__lock__free__node_1a3a90426cd3ddbe8b41768fa95208c1ac) 

#### `typedef `[`node_type`](#structtask__scheduler_1_1atomic__lock__free__node_1a20eeeada550deb5546bdcbbb471216f4) 

# struct `task_scheduler::atomic_lock_free_node_ptr` 

```
struct task_scheduler::atomic_lock_free_node_ptr
  : public TMemInterface
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`Data`](#uniontask__scheduler_1_1atomic__lock__free__node__ptr_1_1Data)` `[`data`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1a31a7ffa3e1c70411773c8e55a4259c00) | 
`public inline void `[`clear`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1aa095f88d78a6eee4497f81864163f91d)`()` | 
`public inline bool `[`compare_exchange_weak`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1a86c19fc0f129338218df9652b0237d6b)`(`[`atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr)` & comperand,`[`atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr)` & value)` | 
`public inline void `[`operator=`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1a5ad29f464e481f03c1beeb6c809cd047)`(const volatile `[`atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr)` & other)` | 
`public inline  `[`atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1aa3f8792d182bc3001938bade102f2f63)`()` | 
`public inline  `[`~atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1a5e587f5fc5febd0e7e7b55c30bf75902)`()` | 
`typedef `[`atomic_node`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1ad49f46f28dfc7670ede880c730ef15df) | 

## Members

#### `public `[`Data`](#uniontask__scheduler_1_1atomic__lock__free__node__ptr_1_1Data)` `[`data`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1a31a7ffa3e1c70411773c8e55a4259c00) 

#### `public inline void `[`clear`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1aa095f88d78a6eee4497f81864163f91d)`()` 

#### `public inline bool `[`compare_exchange_weak`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1a86c19fc0f129338218df9652b0237d6b)`(`[`atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr)` & comperand,`[`atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr)` & value)` 

#### `public inline void `[`operator=`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1a5ad29f464e481f03c1beeb6c809cd047)`(const volatile `[`atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr)` & other)` 

#### `public inline  `[`atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1aa3f8792d182bc3001938bade102f2f63)`()` 

#### `public inline  `[`~atomic_lock_free_node_ptr`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1a5e587f5fc5febd0e7e7b55c30bf75902)`()` 

#### `typedef `[`atomic_node`](#structtask__scheduler_1_1atomic__lock__free__node__ptr_1ad49f46f28dfc7670ede880c730ef15df) 

# struct `task_scheduler::base_sub_graph` 

```
struct task_scheduler::base_sub_graph
  : public TMemInterface
```  

Struct [base_sub_graph](#structtask__scheduler_1_1base__sub__graph)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public task_vector `[`head_tasks`](#structtask__scheduler_1_1base__sub__graph_1aeedb42218a9a8f1543b826e6320a6f01) | The head tasks
`public task_vector `[`tail_tasks`](#structtask__scheduler_1_1base__sub__graph_1ac9ad4e2382e6a370565a57da717ec0cc) | The tail tasks
`public task_vector `[`task_list`](#structtask__scheduler_1_1base__sub__graph_1a8354a339917e3c73c7c9dd4d9429bafa) | The task list
`typedef `[`task_vector`](#structtask__scheduler_1_1base__sub__graph_1ac30ecda816eacf7e294f5ab5cdc8890d) | 

## Members

#### `public task_vector `[`head_tasks`](#structtask__scheduler_1_1base__sub__graph_1aeedb42218a9a8f1543b826e6320a6f01) 

The head tasks

#### `public task_vector `[`tail_tasks`](#structtask__scheduler_1_1base__sub__graph_1ac9ad4e2382e6a370565a57da717ec0cc) 

The tail tasks

#### `public task_vector `[`task_list`](#structtask__scheduler_1_1base__sub__graph_1a8354a339917e3c73c7c9dd4d9429bafa) 

The task list

#### `typedef `[`task_vector`](#structtask__scheduler_1_1base__sub__graph_1ac30ecda816eacf7e294f5ab5cdc8890d) 

# struct `task_scheduler::base_thread` 

```
struct task_scheduler::base_thread
  : public TMemInterface
```  

Struct [base_thread](#structtask__scheduler_1_1base__thread)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`task_queue_type`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type)` * `[`task_queue`](#structtask__scheduler_1_1base__thread_1a6984d53dd70e3ebe84c5ace721b779c3) | 
`public `[`thread_index_type`](#classtask__scheduler_1_1base__thread__index)` `[`thread_index`](#structtask__scheduler_1_1base__thread_1a9c722576a6b63634ce2068156c9ffd48) | The task queue
`public std::thread::id `[`thread_id`](#structtask__scheduler_1_1base__thread_1a73596073f612894156a539595646868a) | The thread identifier
`public std::thread `[`task_thread`](#structtask__scheduler_1_1base__thread_1ab3a8473e75516efcf839bef7c2cf3be9) | The task thread
`public `[`task_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` `[`allocator`](#structtask__scheduler_1_1base__thread_1a2fa7b13352ad22ac51fdc8c5d5a7a552) | The allocator
`public  `[`base_thread`](#structtask__scheduler_1_1base__thread_1abfea35c09c2578a9a948175cb8aca07f)`(thread_num_t _thread_index,`[`thread_pool`](#classtask__scheduler_1_1base__thread__pool)` * _pool)` | Initializes a new instance of the [base_thread<TMemInterface>](#structtask__scheduler_1_1base__thread_1abfea35c09c2578a9a948175cb8aca07f) struct.
`public  `[`~base_thread`](#structtask__scheduler_1_1base__thread_1a69b98972bfa53ba250a0be86c0956a57)`()` | Finalizes an instance of the [base_thread<TMemInterface>](#structtask__scheduler_1_1base__thread_1abfea35c09c2578a9a948175cb8aca07f) class.
`public void `[`sleep`](#structtask__scheduler_1_1base__thread_1a1e756801d7ed49317ce1710bfb7b31a1)`(bool(thread_type::*)() _wake_up)` | Sleeps the specified wake up.
`public void `[`wake_up`](#structtask__scheduler_1_1base__thread_1ae5eeae238be55982d62bc6033768ca37)`()` | Wakes up.
`public void `[`join`](#structtask__scheduler_1_1base__thread_1af3be75960ca07bd8b72c8a7a73a2aaf9)`()` | Joins this instance.
`typedef `[`task_graph_type`](#structtask__scheduler_1_1base__thread_1ab6573125a504b236ac9bf3179f72b340) | 
`typedef `[`task_type`](#structtask__scheduler_1_1base__thread_1a25c43040fe8dbe1ec9070d610196ca92) | 
`typedef `[`task_queue_type`](#structtask__scheduler_1_1base__thread_1a8e711fc61e120f21096cc14f8ad3862d) | 
`typedef `[`thread_type`](#structtask__scheduler_1_1base__thread_1abbea67684c14be9a489ff13659e3156d) | 
`typedef `[`thread_pool`](#structtask__scheduler_1_1base__thread_1a46920fd01f8eafda9f0eb81ab272da31) | 
`typedef `[`task_memory_allocator_type`](#structtask__scheduler_1_1base__thread_1a5c900dfccc3587e195e40691412b5d6e) | 
`typedef `[`thread_index_type`](#structtask__scheduler_1_1base__thread_1a63764fec153b17e3fc3ee25468594c07) | 
`typedef `[`task_vector`](#structtask__scheduler_1_1base__thread_1a200668289ebd31a850182644077b6aa8) | 

## Members

#### `public `[`task_queue_type`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type)` * `[`task_queue`](#structtask__scheduler_1_1base__thread_1a6984d53dd70e3ebe84c5ace721b779c3) 

#### `public `[`thread_index_type`](#classtask__scheduler_1_1base__thread__index)` `[`thread_index`](#structtask__scheduler_1_1base__thread_1a9c722576a6b63634ce2068156c9ffd48) 

The task queue

#### `public std::thread::id `[`thread_id`](#structtask__scheduler_1_1base__thread_1a73596073f612894156a539595646868a) 

The thread identifier

#### `public std::thread `[`task_thread`](#structtask__scheduler_1_1base__thread_1ab3a8473e75516efcf839bef7c2cf3be9) 

The task thread

#### `public `[`task_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` `[`allocator`](#structtask__scheduler_1_1base__thread_1a2fa7b13352ad22ac51fdc8c5d5a7a552) 

The allocator

#### `public  `[`base_thread`](#structtask__scheduler_1_1base__thread_1abfea35c09c2578a9a948175cb8aca07f)`(thread_num_t _thread_index,`[`thread_pool`](#classtask__scheduler_1_1base__thread__pool)` * _pool)` 

Initializes a new instance of the [base_thread<TMemInterface>](#structtask__scheduler_1_1base__thread_1abfea35c09c2578a9a948175cb8aca07f) struct.

#### Parameters
* `_thread_index` Index of the thread.

* `_pool` The pool.

#### `public  `[`~base_thread`](#structtask__scheduler_1_1base__thread_1a69b98972bfa53ba250a0be86c0956a57)`()` 

Finalizes an instance of the [base_thread<TMemInterface>](#structtask__scheduler_1_1base__thread_1abfea35c09c2578a9a948175cb8aca07f) class.

#### `public void `[`sleep`](#structtask__scheduler_1_1base__thread_1a1e756801d7ed49317ce1710bfb7b31a1)`(bool(thread_type::*)() _wake_up)` 

Sleeps the specified wake up.

#### Parameters
* `_wake_up` The wake up.

#### `public void `[`wake_up`](#structtask__scheduler_1_1base__thread_1ae5eeae238be55982d62bc6033768ca37)`()` 

Wakes up.

#### `public void `[`join`](#structtask__scheduler_1_1base__thread_1af3be75960ca07bd8b72c8a7a73a2aaf9)`()` 

Joins this instance.

#### `typedef `[`task_graph_type`](#structtask__scheduler_1_1base__thread_1ab6573125a504b236ac9bf3179f72b340) 

#### `typedef `[`task_type`](#structtask__scheduler_1_1base__thread_1a25c43040fe8dbe1ec9070d610196ca92) 

#### `typedef `[`task_queue_type`](#structtask__scheduler_1_1base__thread_1a8e711fc61e120f21096cc14f8ad3862d) 

#### `typedef `[`thread_type`](#structtask__scheduler_1_1base__thread_1abbea67684c14be9a489ff13659e3156d) 

#### `typedef `[`thread_pool`](#structtask__scheduler_1_1base__thread_1a46920fd01f8eafda9f0eb81ab272da31) 

#### `typedef `[`task_memory_allocator_type`](#structtask__scheduler_1_1base__thread_1a5c900dfccc3587e195e40691412b5d6e) 

#### `typedef `[`thread_index_type`](#structtask__scheduler_1_1base__thread_1a63764fec153b17e3fc3ee25468594c07) 

#### `typedef `[`task_vector`](#structtask__scheduler_1_1base__thread_1a200668289ebd31a850182644077b6aa8) 

# struct `task_scheduler::lock_free_node` 

```
struct task_scheduler::lock_free_node
  : public TMemInterface
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`atomic_node`](#structtask__scheduler_1_1atomic__lock__free__node)` `[`next`](#structtask__scheduler_1_1lock__free__node_1a73188aaac7eefda88b855b38017a1de2) | 
`public T `[`value`](#structtask__scheduler_1_1lock__free__node_1a0dbc4105428987e856f47b9aac18f1f1) | 
`public inline  explicit `[`operator void *`](#structtask__scheduler_1_1lock__free__node_1a21f15e1be670c3af1e9bd180f28f8c7d)`() const` | 
`public inline  `[`lock_free_node`](#structtask__scheduler_1_1lock__free__node_1abcffb4861002883c353a1d8e6b12da7a)`()` | 
`public inline const T & `[`load`](#structtask__scheduler_1_1lock__free__node_1ad16795dfba2fc5b5eb191e5469c9de1e)`() const` | 
`public inline void `[`store`](#structtask__scheduler_1_1lock__free__node_1a1d11b194ca179dd7fbc5e50ffac975c6)`(const T & _value)` | 
`typedef `[`atomic_node`](#structtask__scheduler_1_1lock__free__node_1a3dfac4ce5b68efcb6c801cc436813894) | 

## Members

#### `public `[`atomic_node`](#structtask__scheduler_1_1atomic__lock__free__node)` `[`next`](#structtask__scheduler_1_1lock__free__node_1a73188aaac7eefda88b855b38017a1de2) 

#### `public T `[`value`](#structtask__scheduler_1_1lock__free__node_1a0dbc4105428987e856f47b9aac18f1f1) 

#### `public inline  explicit `[`operator void *`](#structtask__scheduler_1_1lock__free__node_1a21f15e1be670c3af1e9bd180f28f8c7d)`() const` 

#### `public inline  `[`lock_free_node`](#structtask__scheduler_1_1lock__free__node_1abcffb4861002883c353a1d8e6b12da7a)`()` 

#### `public inline const T & `[`load`](#structtask__scheduler_1_1lock__free__node_1ad16795dfba2fc5b5eb191e5469c9de1e)`() const` 

#### `public inline void `[`store`](#structtask__scheduler_1_1lock__free__node_1a1d11b194ca179dd7fbc5e50ffac975c6)`(const T & _value)` 

#### `typedef `[`atomic_node`](#structtask__scheduler_1_1lock__free__node_1a3dfac4ce5b68efcb6c801cc436813894) 

# struct `task_scheduler::out_t` 

Struct [out_t](#structtask__scheduler_1_1out__t)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public template<>`  <br/>`inline `[`out_t`](#structtask__scheduler_1_1out__t)` & `[`operator<<`](#structtask__scheduler_1_1out__t_1a20c0708340b13a6c8b3d3cc3abbf193e)`(T && x)` | Operators the specified x.

## Members

#### `public template<>`  <br/>`inline `[`out_t`](#structtask__scheduler_1_1out__t)` & `[`operator<<`](#structtask__scheduler_1_1out__t_1a20c0708340b13a6c8b3d3cc3abbf193e)`(T && x)` 

Operators the specified x.

#### Parameters
* `x` The x.

#### Returns
[task_scheduler.out_t](#structtask__scheduler_1_1out__t) &.

# struct `task_scheduler::thread_unsafe_access_storage` 

Struct [thread_unsafe_access_storage](#structtask__scheduler_1_1thread__unsafe__access__storage)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::atomic_int64_t `[`last_thread_id`](#structtask__scheduler_1_1thread__unsafe__access__storage_1a48bf47154811e244a827bd5ea116c95b) | The last thread identifier
`public inline  `[`thread_unsafe_access_storage`](#structtask__scheduler_1_1thread__unsafe__access__storage_1a07517482cd35b91ded7003ea7f10cf60)`()` | Initializes a new instance of the [thread_unsafe_access_storage](#structtask__scheduler_1_1thread__unsafe__access__storage) struct.

## Members

#### `public std::atomic_int64_t `[`last_thread_id`](#structtask__scheduler_1_1thread__unsafe__access__storage_1a48bf47154811e244a827bd5ea116c95b) 

The last thread identifier

#### `public inline  `[`thread_unsafe_access_storage`](#structtask__scheduler_1_1thread__unsafe__access__storage_1a07517482cd35b91ded7003ea7f10cf60)`()` 

Initializes a new instance of the [thread_unsafe_access_storage](#structtask__scheduler_1_1thread__unsafe__access__storage) struct.

# namespace `task_scheduler::atomics` 

The atomics namespace.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline int64_t `[`increment`](#namespacetask__scheduler_1_1atomics_1ac6aa29d9a55c34b5c4c25bc117251bac)`(volatile int64_t & _data)`            | Increments the specified data.
`public inline int64_t `[`decrement`](#namespacetask__scheduler_1_1atomics_1a573cf9e05bb2284a187ad0e6f5808112)`(volatile int64_t & _data)`            | Decrements the specified data.
`public inline int32_t `[`increment`](#namespacetask__scheduler_1_1atomics_1af733451a4957a7d7cedc202c3ad487e4)`(volatile int32_t & _data)`            | Increments the specified data.
`public inline int32_t `[`decrement`](#namespacetask__scheduler_1_1atomics_1a6153c8b9258ad21047f107e1fccb844f)`(volatile int32_t & _data)`            | Decrements the specified data.
`public inline int32_t `[`compare_exchange_weak`](#namespacetask__scheduler_1_1atomics_1af5c3557bac9d04bffc9c20bde75b1a7d)`(volatile int32_t & _data,int32_t _comperand,int32_t _value)`            | Compares the exchange weak.
`public inline int64_t `[`compare_exchange_weak`](#namespacetask__scheduler_1_1atomics_1ae80207c11a7e20ad05aa84f64cc9920d)`(volatile int64_t & _data,int64_t _comperand,int64_t _value)`            | Compares the exchange weak.
`public template<>`  <br/>`inline T * `[`compare_exchange_weak`](#namespacetask__scheduler_1_1atomics_1a5cb2b007eb9a48b4872ce79f26189cd1)`(T *volatile & _data,T * _comperand,T * _value)`            | Compares the exchange weak.
`public inline bool `[`compare_exchange_weak_128`](#namespacetask__scheduler_1_1atomics_1a762575bf79144aa7342206f1ce331512)`(volatile int64_t _data,int64_t _comperand,int64_t _value_hi,int64_t _value_lo)`            | Compares the exchange weak 128.

## Members

#### `public inline int64_t `[`increment`](#namespacetask__scheduler_1_1atomics_1ac6aa29d9a55c34b5c4c25bc117251bac)`(volatile int64_t & _data)` 

Increments the specified data.

#### Parameters
* `_data` The data.

#### Returns
int64_t.

#### `public inline int64_t `[`decrement`](#namespacetask__scheduler_1_1atomics_1a573cf9e05bb2284a187ad0e6f5808112)`(volatile int64_t & _data)` 

Decrements the specified data.

#### Parameters
* `_data` The data.

#### Returns
int64_t.

#### `public inline int32_t `[`increment`](#namespacetask__scheduler_1_1atomics_1af733451a4957a7d7cedc202c3ad487e4)`(volatile int32_t & _data)` 

Increments the specified data.

#### Parameters
* `_data` The data.

#### Returns
int32_t.

#### `public inline int32_t `[`decrement`](#namespacetask__scheduler_1_1atomics_1a6153c8b9258ad21047f107e1fccb844f)`(volatile int32_t & _data)` 

Decrements the specified data.

#### Parameters
* `_data` The data.

#### Returns
int32_t.

#### `public inline int32_t `[`compare_exchange_weak`](#namespacetask__scheduler_1_1atomics_1af5c3557bac9d04bffc9c20bde75b1a7d)`(volatile int32_t & _data,int32_t _comperand,int32_t _value)` 

Compares the exchange weak.

#### Parameters
* `_data` The data.

* `_comperand` The comperand.

* `_value` The value.

#### Returns
int32_t.

#### `public inline int64_t `[`compare_exchange_weak`](#namespacetask__scheduler_1_1atomics_1ae80207c11a7e20ad05aa84f64cc9920d)`(volatile int64_t & _data,int64_t _comperand,int64_t _value)` 

Compares the exchange weak.

#### Parameters
* `_data` The data.

* `_comperand` The comperand.

* `_value` The value.

#### Returns
int64_t.

#### `public template<>`  <br/>`inline T * `[`compare_exchange_weak`](#namespacetask__scheduler_1_1atomics_1a5cb2b007eb9a48b4872ce79f26189cd1)`(T *volatile & _data,T * _comperand,T * _value)` 

Compares the exchange weak.

#### Parameters
* `_data` The data.

* `_comperand` The comperand.

* `_value` The value.

#### Returns
T *.

#### `public inline bool `[`compare_exchange_weak_128`](#namespacetask__scheduler_1_1atomics_1a762575bf79144aa7342206f1ce331512)`(volatile int64_t _data,int64_t _comperand,int64_t _value_hi,int64_t _value_lo)` 

Compares the exchange weak 128.

#### Parameters
* `_data` The data.

* `_comperand` The comperand.

* `_value_hi` The value hi.

* `_value_lo` The value lo.

#### Returns
bool.

# namespace `task_scheduler::profile` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public template<>`  <br/>`TReturnType `[`instrument`](#profilebase_8h_1a1ab85b524c825d15ab11f0e21f7f835c)`(time & _profileTime,TClassType * _classType,TMemFunc _func,TArgs... _params)`            | Instruments the specified profile time.
`public inline void `[`suppress`](#profilebase_8h_1aa9d8bb2173b183ae210481908a115e22)`()`            | 
`public inline void `[`unsuppress`](#profilebase_8h_1a67fd7146f855d744139ca0cc8234df24)`()`            | 
`public template<>`  <br/>`static `[`errors`](#classtask__scheduler_1_1profile_1_1errors)` * `[`instance`](#profileitt_8h_1a1b4fdd633b3c8446b8837093c2d15a72)`()`            | 
`public static `[`errors`](#classtask__scheduler_1_1profile_1_1errors)` * `[`instance`](#profilenone_8h_1abe1ba83ba44e6e0603b23713c366b7ef)`()`            | 
`class `[`task_scheduler::profile::basic_errors`](#classtask__scheduler_1_1profile_1_1basic__errors) | 
`class `[`task_scheduler::profile::basic_string`](#classtask__scheduler_1_1profile_1_1basic__string) | 
`class `[`task_scheduler::profile::domain`](#classtask__scheduler_1_1profile_1_1domain) | 
`class `[`task_scheduler::profile::domain_itt`](#classtask__scheduler_1_1profile_1_1domain__itt) | 
`class `[`task_scheduler::profile::error_stack`](#classtask__scheduler_1_1profile_1_1error__stack) | 
`class `[`task_scheduler::profile::errors`](#classtask__scheduler_1_1profile_1_1errors) | 
`class `[`task_scheduler::profile::function`](#classtask__scheduler_1_1profile_1_1function) | 
`class `[`task_scheduler::profile::id`](#classtask__scheduler_1_1profile_1_1id) | 
`class `[`task_scheduler::profile::itt_errors`](#classtask__scheduler_1_1profile_1_1itt__errors) | 
`class `[`task_scheduler::profile::itt_string`](#classtask__scheduler_1_1profile_1_1itt__string) | 
`class `[`task_scheduler::profile::memory`](#classtask__scheduler_1_1profile_1_1memory) | 
`class `[`task_scheduler::profile::memory_itt`](#classtask__scheduler_1_1profile_1_1memory__itt) | 
`class `[`task_scheduler::profile::null_string`](#classtask__scheduler_1_1profile_1_1null__string) | 
`class `[`task_scheduler::profile::profile_mem_interface`](#classtask__scheduler_1_1profile_1_1profile__mem__interface) | Class [profile_mem_interface](#classtask__scheduler_1_1profile_1_1profile__mem__interface).
`class `[`task_scheduler::profile::task`](#classtask__scheduler_1_1profile_1_1task) | 
`struct `[`task_scheduler::profile::task_param`](#structtask__scheduler_1_1profile_1_1task__param) | 
`struct `[`task_scheduler::profile::timer`](#structtask__scheduler_1_1profile_1_1timer) | Struct timer

## Members

#### `public template<>`  <br/>`TReturnType `[`instrument`](#profilebase_8h_1a1ab85b524c825d15ab11f0e21f7f835c)`(time & _profileTime,TClassType * _classType,TMemFunc _func,TArgs... _params)` 

Instruments the specified profile time.

#### Parameters
* `_profileTime` The profile time.

* `_classType` Type of the class.

* `_func` The function.

* `..._params` The ... parameters.

#### Returns
TReturnType.

#### `public inline void `[`suppress`](#profilebase_8h_1aa9d8bb2173b183ae210481908a115e22)`()` 

#### `public inline void `[`unsuppress`](#profilebase_8h_1a67fd7146f855d744139ca0cc8234df24)`()` 

#### `public template<>`  <br/>`static `[`errors`](#classtask__scheduler_1_1profile_1_1errors)` * `[`instance`](#profileitt_8h_1a1b4fdd633b3c8446b8837093c2d15a72)`()` 

#### `public static `[`errors`](#classtask__scheduler_1_1profile_1_1errors)` * `[`instance`](#profilenone_8h_1abe1ba83ba44e6e0603b23713c366b7ef)`()` 

# class `task_scheduler::profile::basic_errors` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void `[`suppress`](#classtask__scheduler_1_1profile_1_1basic__errors_1a19367e058cddfd3210485076c1d6cbec)`(enum errors::type _error)` | 
`public inline void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1basic__errors_1a9a31c03df94202e20cb113fd2e585002)`(enum errors::type _error)` | 

## Members

#### `public inline void `[`suppress`](#classtask__scheduler_1_1profile_1_1basic__errors_1a19367e058cddfd3210485076c1d6cbec)`(enum errors::type _error)` 

#### `public inline void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1basic__errors_1a9a31c03df94202e20cb113fd2e585002)`(enum errors::type _error)` 

# class `task_scheduler::profile::basic_string` 

```
class task_scheduler::profile::basic_string
  : public TStringImplementation
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`basic_string`](#classtask__scheduler_1_1profile_1_1basic__string_1addbe16e66f2966e21007ed8f46ef2a3c)`(const tchar_t * _name)` | 
`public inline TStringImplementation::handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1basic__string_1a7c9d50d37343a1620ac2238d8d6a4403)`()` | 

## Members

#### `public inline  `[`basic_string`](#classtask__scheduler_1_1profile_1_1basic__string_1addbe16e66f2966e21007ed8f46ef2a3c)`(const tchar_t * _name)` 

#### `public inline TStringImplementation::handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1basic__string_1a7c9d50d37343a1620ac2238d8d6a4403)`()` 

# class `task_scheduler::profile::domain` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`ts_declare_attribute_and_callbacks`](#classtask__scheduler_1_1profile_1_1domain_1adbaf633fa84a0f27a041f3f4435cd36c)`(`[`domain`](#classtask__scheduler_1_1profile_1_1domain)`,const tchar_t *,name)` | 
`public inline  `[`domain`](#classtask__scheduler_1_1profile_1_1domain_1af029b5c0bd5ab0a81970eb84c627cd2d)`()` | 
`public inline virtual handle `[`operator*`](#classtask__scheduler_1_1profile_1_1domain_1a608d01b9a24f301ca0cd333031cb32a5)`()` | 
`typedef `[`handle`](#classtask__scheduler_1_1profile_1_1domain_1aa276e0cc614bbdf563dc14894c3e069f) | 

## Members

#### `public  `[`ts_declare_attribute_and_callbacks`](#classtask__scheduler_1_1profile_1_1domain_1adbaf633fa84a0f27a041f3f4435cd36c)`(`[`domain`](#classtask__scheduler_1_1profile_1_1domain)`,const tchar_t *,name)` 

#### `public inline  `[`domain`](#classtask__scheduler_1_1profile_1_1domain_1af029b5c0bd5ab0a81970eb84c627cd2d)`()` 

#### `public inline virtual handle `[`operator*`](#classtask__scheduler_1_1profile_1_1domain_1a608d01b9a24f301ca0cd333031cb32a5)`()` 

#### `typedef `[`handle`](#classtask__scheduler_1_1profile_1_1domain_1aa276e0cc614bbdf563dc14894c3e069f) 

# class `task_scheduler::profile::domain_itt` 

```
class task_scheduler::profile::domain_itt
  : public task_scheduler::profile::domain
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void `[`set_name`](#classtask__scheduler_1_1profile_1_1domain__itt_1a9fe771642ef7e6df3682d46e86758228)`(const tchar_t * _name)` | 
`public inline virtual super::handle `[`operator*`](#classtask__scheduler_1_1profile_1_1domain__itt_1a2f776b8d308099dc200f4418eb01d571)`()` | 
`public inline __itt_domain * `[`get_domain`](#classtask__scheduler_1_1profile_1_1domain__itt_1a7862391a1b316a368111389f67332951)`() const` | 

## Members

#### `public inline void `[`set_name`](#classtask__scheduler_1_1profile_1_1domain__itt_1a9fe771642ef7e6df3682d46e86758228)`(const tchar_t * _name)` 

#### `public inline virtual super::handle `[`operator*`](#classtask__scheduler_1_1profile_1_1domain__itt_1a2f776b8d308099dc200f4418eb01d571)`()` 

#### `public inline __itt_domain * `[`get_domain`](#classtask__scheduler_1_1profile_1_1domain__itt_1a7862391a1b316a368111389f67332951)`() const` 

# class `task_scheduler::profile::error_stack` 

```
class task_scheduler::profile::error_stack
  : public task_scheduler::profile::errors
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline virtual void `[`suppress`](#classtask__scheduler_1_1profile_1_1error__stack_1ac725bc4ad9d5475fcb68a3709dab6ef7)`(enum type _error)` | 
`public inline virtual void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1error__stack_1a13417ca3e8efe01803dde3997afc043e)`(enum type _error)` | 

## Members

#### `public inline virtual void `[`suppress`](#classtask__scheduler_1_1profile_1_1error__stack_1ac725bc4ad9d5475fcb68a3709dab6ef7)`(enum type _error)` 

#### `public inline virtual void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1error__stack_1a13417ca3e8efe01803dde3997afc043e)`(enum type _error)` 

# class `task_scheduler::profile::errors` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`suppress`](#classtask__scheduler_1_1profile_1_1errors_1a94f9572c4ce5e0a5d9ddeb49f7dae93d)`(enum type _error)` | 
`public void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1errors_1a019f780eb8d7832fdf7f48eb65eca4a8)`(enum type _error)` | 
`enum `[`type`](#classtask__scheduler_1_1profile_1_1errors_1a326517657da7b5c8b07a0f297323628f) | 

## Members

#### `public void `[`suppress`](#classtask__scheduler_1_1profile_1_1errors_1a94f9572c4ce5e0a5d9ddeb49f7dae93d)`(enum type _error)` 

#### `public void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1errors_1a019f780eb8d7832fdf7f48eb65eca4a8)`(enum type _error)` 

#### `enum `[`type`](#classtask__scheduler_1_1profile_1_1errors_1a326517657da7b5c8b07a0f297323628f) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
threads            | 
memory            | 
all            | 

# class `task_scheduler::profile::function` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public template<>`  <br/>`inline  `[`function`](#classtask__scheduler_1_1profile_1_1function_1a15ae633f651f376b9d327caccefe547b)`(TFuncType _func)` | 
`public inline handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1function_1aff318dc3e5619fc1d20564d5c2f17c14)`()` | 

## Members

#### `public template<>`  <br/>`inline  `[`function`](#classtask__scheduler_1_1profile_1_1function_1a15ae633f651f376b9d327caccefe547b)`(TFuncType _func)` 

#### `public inline handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1function_1aff318dc3e5619fc1d20564d5c2f17c14)`()` 

# class `task_scheduler::profile::id` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`id`](#classtask__scheduler_1_1profile_1_1id_1a80fc1a989279a76e5dbde587031bcf79)`(const tchar_t * _name)` | 
`public inline handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1id_1a7f4df85ee2ba36ca0563573d13c39331)`()` | 

## Members

#### `public inline  `[`id`](#classtask__scheduler_1_1profile_1_1id_1a80fc1a989279a76e5dbde587031bcf79)`(const tchar_t * _name)` 

#### `public inline handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1id_1a7f4df85ee2ba36ca0563573d13c39331)`()` 

# class `task_scheduler::profile::itt_errors` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline uint32_t `[`get_itt_error`](#classtask__scheduler_1_1profile_1_1itt__errors_1afc3540725f9cbc2683436f0adda3c95d)`(enum errors::type _error)` | 
`public inline void `[`suppress`](#classtask__scheduler_1_1profile_1_1itt__errors_1aadb0c9cdf5e7f7f34e02a3311c152d85)`(enum errors::type _error)` | 
`public inline void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1itt__errors_1ad66b2c0296fd43734130cf26bc682617)`(enum errors::type _error)` | 

## Members

#### `public inline uint32_t `[`get_itt_error`](#classtask__scheduler_1_1profile_1_1itt__errors_1afc3540725f9cbc2683436f0adda3c95d)`(enum errors::type _error)` 

#### `public inline void `[`suppress`](#classtask__scheduler_1_1profile_1_1itt__errors_1aadb0c9cdf5e7f7f34e02a3311c152d85)`(enum errors::type _error)` 

#### `public inline void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1itt__errors_1ad66b2c0296fd43734130cf26bc682617)`(enum errors::type _error)` 

# class `task_scheduler::profile::itt_string` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`itt_string`](#classtask__scheduler_1_1profile_1_1itt__string_1a633213abb3230a6afb35297a2666933e)`(const tchar_t * _name)` | 
`public inline handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1itt__string_1a62b6a1baa9088ce5e316a646303f6313)`()` | 
`typedef `[`handle`](#classtask__scheduler_1_1profile_1_1itt__string_1a51685b457f1653625cd65748f5c3a807) | 

## Members

#### `public inline  `[`itt_string`](#classtask__scheduler_1_1profile_1_1itt__string_1a633213abb3230a6afb35297a2666933e)`(const tchar_t * _name)` 

#### `public inline handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1itt__string_1a62b6a1baa9088ce5e316a646303f6313)`()` 

#### `typedef `[`handle`](#classtask__scheduler_1_1profile_1_1itt__string_1a51685b457f1653625cd65748f5c3a807) 

# class `task_scheduler::profile::memory` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`ts_declare_attribute_and_callbacks`](#classtask__scheduler_1_1profile_1_1memory_1ac8cbc4339fa5125887f595f377d76648)`(`[`memory`](#classtask__scheduler_1_1profile_1_1memory)`,const tchar_t *,name)` | 
`public inline  `[`memory`](#classtask__scheduler_1_1profile_1_1memory_1a3b586517629971d0d1071d81046842d9)`()` | 
`public inline void `[`suppress`](#classtask__scheduler_1_1profile_1_1memory_1ae0fb7087d07e485550c53115aabdb993)`()` | 
`public inline void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1memory_1a6d0585fd5fab9bfdb3a9017471adc845)`()` | 
`public inline virtual void `[`allocate_begin`](#classtask__scheduler_1_1profile_1_1memory_1aabef32065f5f5c116e77dca4f0956fd1)`(size_t _size,bool _initialized)` | 
`public inline virtual void `[`allocate_end`](#classtask__scheduler_1_1profile_1_1memory_1a8b90fc92ba25c91816a1af3cddce261e)`(void ** _memory_allocation,size_t _size,bool _initialized)` | 

## Members

#### `public  `[`ts_declare_attribute_and_callbacks`](#classtask__scheduler_1_1profile_1_1memory_1ac8cbc4339fa5125887f595f377d76648)`(`[`memory`](#classtask__scheduler_1_1profile_1_1memory)`,const tchar_t *,name)` 

#### `public inline  `[`memory`](#classtask__scheduler_1_1profile_1_1memory_1a3b586517629971d0d1071d81046842d9)`()` 

#### `public inline void `[`suppress`](#classtask__scheduler_1_1profile_1_1memory_1ae0fb7087d07e485550c53115aabdb993)`()` 

#### `public inline void `[`unsuppress`](#classtask__scheduler_1_1profile_1_1memory_1a6d0585fd5fab9bfdb3a9017471adc845)`()` 

#### `public inline virtual void `[`allocate_begin`](#classtask__scheduler_1_1profile_1_1memory_1aabef32065f5f5c116e77dca4f0956fd1)`(size_t _size,bool _initialized)` 

#### `public inline virtual void `[`allocate_end`](#classtask__scheduler_1_1profile_1_1memory_1a8b90fc92ba25c91816a1af3cddce261e)`(void ** _memory_allocation,size_t _size,bool _initialized)` 

# class `task_scheduler::profile::memory_itt` 

```
class task_scheduler::profile::memory_itt
  : public task_scheduler::profile::memory
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`set_name`](#classtask__scheduler_1_1profile_1_1memory__itt_1a97bcd4d270b968ed70abdec20df461d3)`(const tchar_t * _name)` | 
`public inline virtual void `[`allocate_begin`](#classtask__scheduler_1_1profile_1_1memory__itt_1a0d3eec07c204c528a3fdfe93196b63b1)`(size_t _size,bool _initialized)` | 
`public inline virtual void `[`allocate_end`](#classtask__scheduler_1_1profile_1_1memory__itt_1a2057743c3c3672fd67eb6a7d0441cd5b)`(void ** _memory_allocation,size_t _size,bool _initialized)` | 
`typedef `[`super`](#classtask__scheduler_1_1profile_1_1memory__itt_1a4105108c24683d47b9bef40011648c75) | 

## Members

#### `public void `[`set_name`](#classtask__scheduler_1_1profile_1_1memory__itt_1a97bcd4d270b968ed70abdec20df461d3)`(const tchar_t * _name)` 

#### `public inline virtual void `[`allocate_begin`](#classtask__scheduler_1_1profile_1_1memory__itt_1a0d3eec07c204c528a3fdfe93196b63b1)`(size_t _size,bool _initialized)` 

#### `public inline virtual void `[`allocate_end`](#classtask__scheduler_1_1profile_1_1memory__itt_1a2057743c3c3672fd67eb6a7d0441cd5b)`(void ** _memory_allocation,size_t _size,bool _initialized)` 

#### `typedef `[`super`](#classtask__scheduler_1_1profile_1_1memory__itt_1a4105108c24683d47b9bef40011648c75) 

# class `task_scheduler::profile::null_string` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`protected inline  `[`null_string`](#classtask__scheduler_1_1profile_1_1null__string_1a1d5e4782a791a9b802b3641707590007)`(const tchar_t * _name)` | 
`protected inline handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1null__string_1a7c68411585255dfe69c0b3361c7389d5)`()` | 

## Members

#### `protected inline  `[`null_string`](#classtask__scheduler_1_1profile_1_1null__string_1a1d5e4782a791a9b802b3641707590007)`(const tchar_t * _name)` 

#### `protected inline handle & `[`operator*`](#classtask__scheduler_1_1profile_1_1null__string_1a7c68411585255dfe69c0b3361c7389d5)`()` 

# class `task_scheduler::profile::profile_mem_interface` 

Class [profile_mem_interface](#classtask__scheduler_1_1profile_1_1profile__mem__interface).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `task_scheduler::profile::task` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline bool `[`exit`](#classtask__scheduler_1_1profile_1_1task_1a00ec37c3933c49e52d77cfbdcc6818d9)`(`[`task_param`](#structtask__scheduler_1_1profile_1_1task__param)` & param)` | 
`public inline  `[`task`](#classtask__scheduler_1_1profile_1_1task_1a2d375bcd66f05cbb4316b258540c10b6)`()` | 
`public inline bool `[`enter`](#classtask__scheduler_1_1profile_1_1task_1af088c778a93b0401e3b855ff07289ad1)`(`[`task_param`](#structtask__scheduler_1_1profile_1_1task__param)` & _param)` | 
`public inline bool `[`exit`](#classtask__scheduler_1_1profile_1_1task_1a2430f9008eed105b7985feb18692bea5)`(`[`task_param`](#structtask__scheduler_1_1profile_1_1task__param)` & _param)` | 

## Members

#### `public inline bool `[`exit`](#classtask__scheduler_1_1profile_1_1task_1a00ec37c3933c49e52d77cfbdcc6818d9)`(`[`task_param`](#structtask__scheduler_1_1profile_1_1task__param)` & param)` 

#### `public inline  `[`task`](#classtask__scheduler_1_1profile_1_1task_1a2d375bcd66f05cbb4316b258540c10b6)`()` 

#### `public inline bool `[`enter`](#classtask__scheduler_1_1profile_1_1task_1af088c778a93b0401e3b855ff07289ad1)`(`[`task_param`](#structtask__scheduler_1_1profile_1_1task__param)` & _param)` 

#### `public inline bool `[`exit`](#classtask__scheduler_1_1profile_1_1task_1a2430f9008eed105b7985feb18692bea5)`(`[`task_param`](#structtask__scheduler_1_1profile_1_1task__param)` & _param)` 

# struct `task_scheduler::profile::task_param` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`function`](#classtask__scheduler_1_1profile_1_1function)` `[`task_function`](#structtask__scheduler_1_1profile_1_1task__param_1a9fd73cf32ef4cd1186f9c3dc8dd83086) | 
`public `[`id`](#classtask__scheduler_1_1profile_1_1id)` `[`task_id`](#structtask__scheduler_1_1profile_1_1task__param_1a6b17f9cf74640fcf533081c0a56321f7) | 
`public `[`id`](#classtask__scheduler_1_1profile_1_1id)` `[`parent_task_id`](#structtask__scheduler_1_1profile_1_1task__param_1a93ac432e81d23072a3e6e03bf3cddbf2) | 
`public `[`string`](#classtask__scheduler_1_1profile_1_1basic__string)` `[`task_name`](#structtask__scheduler_1_1profile_1_1task__param_1a3bac2a4ba7d0b79efca5824c21430aeb) | 
`public inline  `[`task_param`](#structtask__scheduler_1_1profile_1_1task__param_1a88d213681e17095bf837a4b73ca7fcd7)`(`[`function`](#classtask__scheduler_1_1profile_1_1function)` _func,const tchar_t * _task_id,const tchar_t * _parent_task_id,const tchar_t * _task_name)` | 

## Members

#### `public `[`function`](#classtask__scheduler_1_1profile_1_1function)` `[`task_function`](#structtask__scheduler_1_1profile_1_1task__param_1a9fd73cf32ef4cd1186f9c3dc8dd83086) 

#### `public `[`id`](#classtask__scheduler_1_1profile_1_1id)` `[`task_id`](#structtask__scheduler_1_1profile_1_1task__param_1a6b17f9cf74640fcf533081c0a56321f7) 

#### `public `[`id`](#classtask__scheduler_1_1profile_1_1id)` `[`parent_task_id`](#structtask__scheduler_1_1profile_1_1task__param_1a93ac432e81d23072a3e6e03bf3cddbf2) 

#### `public `[`string`](#classtask__scheduler_1_1profile_1_1basic__string)` `[`task_name`](#structtask__scheduler_1_1profile_1_1task__param_1a3bac2a4ba7d0b79efca5824c21430aeb) 

#### `public inline  `[`task_param`](#structtask__scheduler_1_1profile_1_1task__param_1a88d213681e17095bf837a4b73ca7fcd7)`(`[`function`](#classtask__scheduler_1_1profile_1_1function)` _func,const tchar_t * _task_id,const tchar_t * _parent_task_id,const tchar_t * _task_name)` 

# struct `task_scheduler::profile::timer` 

Struct timer

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public time_point `[`start`](#structtask__scheduler_1_1profile_1_1timer_1aec08246cc15317c337476d40c1e007ee) | The start
`public time & `[`elapsedTime`](#structtask__scheduler_1_1profile_1_1timer_1a5ac4f91e4bacd2bbc6fc4ec93941cc05) | The elapsed time
`public inline  `[`timer`](#structtask__scheduler_1_1profile_1_1timer_1a785e4fb2c1a923ab869eed84cace2732)`(std::chrono::microseconds & _elapsedTime)` | Initializes a new instance of the [timer](#structtask__scheduler_1_1profile_1_1timer) struct.
`public inline  `[`~timer`](#structtask__scheduler_1_1profile_1_1timer_1ab3c8e7a0ebb9ff188f78699e53be94b2)`()` | Finalizes an instance of the [timer](#structtask__scheduler_1_1profile_1_1timer) class.

## Members

#### `public time_point `[`start`](#structtask__scheduler_1_1profile_1_1timer_1aec08246cc15317c337476d40c1e007ee) 

The start

#### `public time & `[`elapsedTime`](#structtask__scheduler_1_1profile_1_1timer_1a5ac4f91e4bacd2bbc6fc4ec93941cc05) 

The elapsed time

#### `public inline  `[`timer`](#structtask__scheduler_1_1profile_1_1timer_1a785e4fb2c1a923ab869eed84cace2732)`(std::chrono::microseconds & _elapsedTime)` 

Initializes a new instance of the [timer](#structtask__scheduler_1_1profile_1_1timer) struct.

#### Parameters
* `_elapsedTime` The elapsed time.

#### `public inline  `[`~timer`](#structtask__scheduler_1_1profile_1_1timer_1ab3c8e7a0ebb9ff188f78699e53be94b2)`()` 

Finalizes an instance of the [timer](#structtask__scheduler_1_1profile_1_1timer) class.

# namespace `task_scheduler::profile::thread` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void `[`suppress`](#profilebase_8h_1ae5ff3b7af6adda31a2f042f71b8401e7)`()`            | 
`public inline void `[`unsuppress`](#profilebase_8h_1ad6d5123d67e78798a00a3c52d08ae0e3)`()`            | 
`public inline void `[`set_name`](#profilenone_8h_1a45279a59fc45fd919aea14eeed53187d)`(const tchar_t * _name)`            | 

## Members

#### `public inline void `[`suppress`](#profilebase_8h_1ae5ff3b7af6adda31a2f042f71b8401e7)`()` 

#### `public inline void `[`unsuppress`](#profilebase_8h_1ad6d5123d67e78798a00a3c52d08ae0e3)`()` 

#### `public inline void `[`set_name`](#profilenone_8h_1a45279a59fc45fd919aea14eeed53187d)`(const tchar_t * _name)` 

# class `task_scheduler::base_task_graph::task_queue_type` 

```
class task_scheduler::base_task_graph::task_queue_type
  : public task_scheduler::lock_free_queue< TPolicy, T, TMemInterface, TParam >
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`task_queue_type`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type_1a32a6a4dd1f06f50e211850aeb2313953)`(`[`task_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` * allocator)` | 
`public bool `[`push_back`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type_1a6f2a7f3216b2deeb64d0c217ab3f5187)`(typename `[`base_task](#classtask__scheduler_1_1base__task)< TMemInterface >::[task_type`](#classtask__scheduler_1_1base__task)` * _new_task)` | 
`public inline virtual  `[`~task_queue_type`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type_1a78d4741a576e95b18621afac1a3098b9)`()` | 

## Members

#### `public  `[`task_queue_type`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type_1a32a6a4dd1f06f50e211850aeb2313953)`(`[`task_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` * allocator)` 

#### `public bool `[`push_back`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type_1a6f2a7f3216b2deeb64d0c217ab3f5187)`(typename `[`base_task](#classtask__scheduler_1_1base__task)< TMemInterface >::[task_type`](#classtask__scheduler_1_1base__task)` * _new_task)` 

#### `public inline virtual  `[`~task_queue_type`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type_1a78d4741a576e95b18621afac1a3098b9)`()` 

# struct `task_scheduler::lock_free_node_stack::debug_container` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int32_t `[`counter`](#structtask__scheduler_1_1lock__free__node__stack_1_1debug__container_1ad280bc37155e40cf9f6efaf3664e204f) | 

## Members

#### `public int32_t `[`counter`](#structtask__scheduler_1_1lock__free__node__stack_1_1debug__container_1ad280bc37155e40cf9f6efaf3664e204f) 

# struct `task_scheduler::multi_producer_multi_consumer::debug_container` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int32_t `[`counter`](#structtask__scheduler_1_1multi__producer__multi__consumer_1_1debug__container_1a3a62f2959fd9a921284f340c14940d8b) | 

## Members

#### `public int32_t `[`counter`](#structtask__scheduler_1_1multi__producer__multi__consumer_1_1debug__container_1a3a62f2959fd9a921284f340c14940d8b) 

# struct `task_scheduler::base_task::debug_container` 

Struct [debug_container](#structtask__scheduler_1_1base__task_1_1debug__container)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public string_type `[`task_name`](#structtask__scheduler_1_1base__task_1_1debug__container_1a91287ab3c30b911959ae1b8647598fbf) | The task name
`public string_vector `[`dependent_task_names`](#structtask__scheduler_1_1base__task_1_1debug__container_1ad60b45b325d1439c5b79a946925f44b3) | The dependent task names
`public const tchar_t * `[`priority_to_string`](#structtask__scheduler_1_1base__task_1_1debug__container_1a48bc9b2478dddf3bbc6663a13a29bc5c)`(`[`priority_selector`](#classtask__scheduler_1_1base__task_1aed4fc159d6bb04b606879e7930612eda)` _priority) const` | Priorities to string.

## Members

#### `public string_type `[`task_name`](#structtask__scheduler_1_1base__task_1_1debug__container_1a91287ab3c30b911959ae1b8647598fbf) 

The task name

#### `public string_vector `[`dependent_task_names`](#structtask__scheduler_1_1base__task_1_1debug__container_1ad60b45b325d1439c5b79a946925f44b3) 

The dependent task names

#### `public const tchar_t * `[`priority_to_string`](#structtask__scheduler_1_1base__task_1_1debug__container_1a48bc9b2478dddf3bbc6663a13a29bc5c)`(`[`priority_selector`](#classtask__scheduler_1_1base__task_1aed4fc159d6bb04b606879e7930612eda)` _priority) const` 

Priorities to string.

#### Parameters
* `_priority` The priority.

#### Returns
const char *.

# struct `task_scheduler::base_task_graph::debug_container` 

Struct [debug_container](#structtask__scheduler_1_1base__task__graph_1_1debug__container)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public task_name_to_task_map `[`task_name_to_task`](#structtask__scheduler_1_1base__task__graph_1_1debug__container_1ac77f2265d7eafc020cadf9e85b411b62) | The task name to task
`public task_vector `[`task_list`](#structtask__scheduler_1_1base__task__graph_1_1debug__container_1a016a7721e3b17b66e9598e6eba9fb02c) | The task list

## Members

#### `public task_name_to_task_map `[`task_name_to_task`](#structtask__scheduler_1_1base__task__graph_1_1debug__container_1ac77f2265d7eafc020cadf9e85b411b62) 

The task name to task

#### `public task_vector `[`task_list`](#structtask__scheduler_1_1base__task__graph_1_1debug__container_1a016a7721e3b17b66e9598e6eba9fb02c) 

The task list

# struct `task_scheduler::default_mem_interface::metadata_type` 

Struct metadata_type

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`space`](#structtask__scheduler_1_1default__mem__interface_1_1metadata__type_1a379fab70cba25f0ac16c4e49a9701608) | The space

## Members

#### `public size_t `[`space`](#structtask__scheduler_1_1default__mem__interface_1_1metadata__type_1a379fab70cba25f0ac16c4e49a9701608) 

The space

# struct `task_scheduler::base_task_graph::persistent_container` 

Struct [persistent_container](#structtask__scheduler_1_1base__task__graph_1_1persistent__container)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public task_vector `[`head_tasks`](#structtask__scheduler_1_1base__task__graph_1_1persistent__container_1afb24e0202f75000514da67b0deb6045b) | The head tasks
`public task_vector `[`tail_tasks`](#structtask__scheduler_1_1base__task__graph_1_1persistent__container_1a4807b4652886b4ef036ef0a63f732a49) | The tail tasks
`public sub_graph_vector `[`sub_graphs`](#structtask__scheduler_1_1base__task__graph_1_1persistent__container_1ab79f2e77eeb33ccd187cc74225bb2c76) | The sub graphs

## Members

#### `public task_vector `[`head_tasks`](#structtask__scheduler_1_1base__task__graph_1_1persistent__container_1afb24e0202f75000514da67b0deb6045b) 

The head tasks

#### `public task_vector `[`tail_tasks`](#structtask__scheduler_1_1base__task__graph_1_1persistent__container_1a4807b4652886b4ef036ef0a63f732a49) 

The tail tasks

#### `public sub_graph_vector `[`sub_graphs`](#structtask__scheduler_1_1base__task__graph_1_1persistent__container_1ab79f2e77eeb33ccd187cc74225bb2c76) 

The sub graphs

# struct `task_scheduler::base_task::persistent_container` 

Struct [persistent_container](#structtask__scheduler_1_1base__task_1_1persistent__container)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`priority_selector`](#classtask__scheduler_1_1base__task_1aed4fc159d6bb04b606879e7930612eda)` `[`task_priority`](#structtask__scheduler_1_1base__task_1_1persistent__container_1aeae0a1982121b75f8b6b603f4c2c3b0c) | The task priority
`public task_vector `[`parent_tasks`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a5d5e272c58547ff0a8095dd910ad6845) | The parent tasks
`public task_vector `[`dependent_tasks`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a5fcda37f50b979503afb9aab48f3aaf4) | The dependent tasks
`public task_vector `[`kick_tasks`](#structtask__scheduler_1_1base__task_1_1persistent__container_1ac22a022b6f3cd6c19c79b63e9f42ca42) | The kick tasks
`public `[`sub_graph_type`](#structtask__scheduler_1_1base__sub__graph)` * `[`sub_graph`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a1e0c86a8413c9fe7b933d50129ced7d4) | The sub graph
`public rank_type `[`rank`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a2d04f6a6d49be303a63184b6824bc79b) | The rank
`public uint64_t `[`thread_affinity`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a76b1bbbc667156d28f1554e946425bc1) | The thread affinity
`public task_work_vector `[`task_work`](#structtask__scheduler_1_1base__task_1_1persistent__container_1adaa496d632432da78040ef8274ec44c5) | The task work
`public thread_num_t `[`num_workers`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a08e359ad75dd8db0d1dbbeec151479dc) | User set number of workers to use to run this task
`public  `[`persistent_container`](#structtask__scheduler_1_1base__task_1_1persistent__container_1aab99b000cfe43e76c1d7dc23fad1ae36)`()` | Initializes a new instance of the base_task<TMemInterface>.persistent_container struct.
`public  `[`~persistent_container`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a08660a1103fca5e4cd63a06bde4a0205)`()` | Finalizes an instance of the base_task<TMemInterface>.persistent_container class.

## Members

#### `public `[`priority_selector`](#classtask__scheduler_1_1base__task_1aed4fc159d6bb04b606879e7930612eda)` `[`task_priority`](#structtask__scheduler_1_1base__task_1_1persistent__container_1aeae0a1982121b75f8b6b603f4c2c3b0c) 

The task priority

#### `public task_vector `[`parent_tasks`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a5d5e272c58547ff0a8095dd910ad6845) 

The parent tasks

#### `public task_vector `[`dependent_tasks`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a5fcda37f50b979503afb9aab48f3aaf4) 

The dependent tasks

#### `public task_vector `[`kick_tasks`](#structtask__scheduler_1_1base__task_1_1persistent__container_1ac22a022b6f3cd6c19c79b63e9f42ca42) 

The kick tasks

#### `public `[`sub_graph_type`](#structtask__scheduler_1_1base__sub__graph)` * `[`sub_graph`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a1e0c86a8413c9fe7b933d50129ced7d4) 

The sub graph

#### `public rank_type `[`rank`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a2d04f6a6d49be303a63184b6824bc79b) 

The rank

#### `public uint64_t `[`thread_affinity`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a76b1bbbc667156d28f1554e946425bc1) 

The thread affinity

#### `public task_work_vector `[`task_work`](#structtask__scheduler_1_1base__task_1_1persistent__container_1adaa496d632432da78040ef8274ec44c5) 

The task work

#### `public thread_num_t `[`num_workers`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a08e359ad75dd8db0d1dbbeec151479dc) 

User set number of workers to use to run this task

#### `public  `[`persistent_container`](#structtask__scheduler_1_1base__task_1_1persistent__container_1aab99b000cfe43e76c1d7dc23fad1ae36)`()` 

Initializes a new instance of the base_task<TMemInterface>.persistent_container struct.

#### `public  `[`~persistent_container`](#structtask__scheduler_1_1base__task_1_1persistent__container_1a08660a1103fca5e4cd63a06bde4a0205)`()` 

Finalizes an instance of the base_task<TMemInterface>.persistent_container class.

# struct `task_scheduler::stl_allocator::rebind` 

Struct rebind

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`typedef `[`other`](#structtask__scheduler_1_1stl__allocator_1_1rebind_1ad2dac5570c9b0242925cc89a837a2ac3) | 

## Members

#### `typedef `[`other`](#structtask__scheduler_1_1stl__allocator_1_1rebind_1ad2dac5570c9b0242925cc89a837a2ac3) 

# struct `task_scheduler::base_thread_pool::setup_container` 

Struct [setup_container](#structtask__scheduler_1_1base__thread__pool_1_1setup__container)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::mutex `[`signal`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container_1af16a5f7b6c4cae29a530d65aa48d16e3) | The signal
`public std::condition_variable `[`radio`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container_1a279db34af3e5993de3cc23ea4bb15b0a) | The radio
`public std::atomic_uint32_t `[`thread_sync`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container_1aa01ab4ec30c455a53e0de7587f7b4dab) | The thread synchronize
`public std::atomic< `[`state_selector`](#classtask__scheduler_1_1base__thread__pool_1ae81f4ae71df3ee8f45e5712ecde9af0e)` > `[`request_exit`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container_1aa081a0079e181ccf19e21bf3480a1f17) | The request exit

## Members

#### `public std::mutex `[`signal`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container_1af16a5f7b6c4cae29a530d65aa48d16e3) 

The signal

#### `public std::condition_variable `[`radio`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container_1a279db34af3e5993de3cc23ea4bb15b0a) 

The radio

#### `public std::atomic_uint32_t `[`thread_sync`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container_1aa01ab4ec30c455a53e0de7587f7b4dab) 

The thread synchronize

#### `public std::atomic< `[`state_selector`](#classtask__scheduler_1_1base__thread__pool_1ae81f4ae71df3ee8f45e5712ecde9af0e)` > `[`request_exit`](#structtask__scheduler_1_1base__thread__pool_1_1setup__container_1aa081a0079e181ccf19e21bf3480a1f17) 

The request exit

# struct `task_scheduler::base_task::transient_container` 

Struct [transient_container](#structtask__scheduler_1_1base__task_1_1transient__container)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::atomic_int64_t `[`start_gate`](#structtask__scheduler_1_1base__task_1_1transient__container_1ac13a5aeef258dfc78a5c11e08a04e46a) | The start gate
`public `[`work_queue_type`](#classtask__scheduler_1_1lock__free__queue)` * `[`work_queue`](#structtask__scheduler_1_1base__task_1_1transient__container_1a5def6b6717fd42c21d3a7450ec9136eb) | The work queue
`public `[`work_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` `[`work_allocator`](#structtask__scheduler_1_1base__task_1_1transient__container_1a395deae9131c38ea685f92dc8f0d5253) | The work allocator
`public std::atomic_int64_t `[`num_working`](#structtask__scheduler_1_1base__task_1_1transient__container_1a0fca87cfedf3e63c6e384de5e3cb5456) | The number working
`public profile::time `[`task_time`](#structtask__scheduler_1_1base__task_1_1transient__container_1aa702267d681fa17d6f520e5da19c0121) | Total time spent running all work functions in this task
`public std::atomic_int64_t `[`num_runned`](#structtask__scheduler_1_1base__task_1_1transient__container_1aa08cc676b18ed50b86426cd206d06fc8) | Total number of times work function was called
`public uint32_t `[`minimum_batch_size`](#structtask__scheduler_1_1base__task_1_1transient__container_1a9f75a5fec4b983d73aea2c1feba5403f) | Calculated minimum batch size
`public  `[`transient_container`](#structtask__scheduler_1_1base__task_1_1transient__container_1a4a0adf23d0c559a0b2599a34ce9e3985)`()` | Initializes a new instance of the base_task<TMemInterface>.transient_container struct.
`public  `[`~transient_container`](#structtask__scheduler_1_1base__task_1_1transient__container_1a0da308091ca9d38292dfca67a49224aa)`()` | Finalizes an instance of the base_task<TMemInterface>.transient_container class.

## Members

#### `public std::atomic_int64_t `[`start_gate`](#structtask__scheduler_1_1base__task_1_1transient__container_1ac13a5aeef258dfc78a5c11e08a04e46a) 

The start gate

#### `public `[`work_queue_type`](#classtask__scheduler_1_1lock__free__queue)` * `[`work_queue`](#structtask__scheduler_1_1base__task_1_1transient__container_1a5def6b6717fd42c21d3a7450ec9136eb) 

The work queue

#### `public `[`work_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` `[`work_allocator`](#structtask__scheduler_1_1base__task_1_1transient__container_1a395deae9131c38ea685f92dc8f0d5253) 

The work allocator

#### `public std::atomic_int64_t `[`num_working`](#structtask__scheduler_1_1base__task_1_1transient__container_1a0fca87cfedf3e63c6e384de5e3cb5456) 

The number working

#### `public profile::time `[`task_time`](#structtask__scheduler_1_1base__task_1_1transient__container_1aa702267d681fa17d6f520e5da19c0121) 

Total time spent running all work functions in this task

#### `public std::atomic_int64_t `[`num_runned`](#structtask__scheduler_1_1base__task_1_1transient__container_1aa08cc676b18ed50b86426cd206d06fc8) 

Total number of times work function was called

#### `public uint32_t `[`minimum_batch_size`](#structtask__scheduler_1_1base__task_1_1transient__container_1a9f75a5fec4b983d73aea2c1feba5403f) 

Calculated minimum batch size

#### `public  `[`transient_container`](#structtask__scheduler_1_1base__task_1_1transient__container_1a4a0adf23d0c559a0b2599a34ce9e3985)`()` 

Initializes a new instance of the base_task<TMemInterface>.transient_container struct.

#### `public  `[`~transient_container`](#structtask__scheduler_1_1base__task_1_1transient__container_1a0da308091ca9d38292dfca67a49224aa)`()` 

Finalizes an instance of the base_task<TMemInterface>.transient_container class.

# struct `task_scheduler::base_task_graph::transient_container` 

Struct [transient_container](#structtask__scheduler_1_1base__task__graph_1_1transient__container)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`task_queue_type`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type)` * `[`task_queue`](#structtask__scheduler_1_1base__task__graph_1_1transient__container_1a5e3026ba753a2b1e572a64b85bcb9428) | The task queue
`public inline  `[`transient_container`](#structtask__scheduler_1_1base__task__graph_1_1transient__container_1a021c666e2e58cb48a14ccb0b40e16a10)`(`[`task_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` * allocator)` | Initializes a new instance of the base_task_graph<TMemInterface>.transient_container struct.
`public inline  `[`~transient_container`](#structtask__scheduler_1_1base__task__graph_1_1transient__container_1a97a14fa37a9f8239d01c272ccc001aea)`()` | Finalizes an instance of the base_task_graph<TMemInterface>.transient_container class.

## Members

#### `public `[`task_queue_type`](#classtask__scheduler_1_1base__task__graph_1_1task__queue__type)` * `[`task_queue`](#structtask__scheduler_1_1base__task__graph_1_1transient__container_1a5e3026ba753a2b1e572a64b85bcb9428) 

The task queue

#### `public inline  `[`transient_container`](#structtask__scheduler_1_1base__task__graph_1_1transient__container_1a021c666e2e58cb48a14ccb0b40e16a10)`(`[`task_memory_allocator_type`](#classtask__scheduler_1_1lock__free__node__dispenser)` * allocator)` 

Initializes a new instance of the base_task_graph<TMemInterface>.transient_container struct.

#### Parameters
* `allocator` The allocator.

#### `public inline  `[`~transient_container`](#structtask__scheduler_1_1base__task__graph_1_1transient__container_1a97a14fa37a9f8239d01c272ccc001aea)`()` 

Finalizes an instance of the base_task_graph<TMemInterface>.transient_container class.

# struct `task_scheduler::base_data_task::transient_data_container` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`data_vector`](#classtask__scheduler_1_1guarded)` `[`data_workload`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1a1ade8d5e1eb8312e998f6cfe3522108d) | Total number of times work function was called
`public `[`data_dispatcher_type`](#classtask__scheduler_1_1lock__free__batch__dispatcher)` * `[`data_dispatcher`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1a52e4c2089b23f0c2f10e7d7afbbc0b11) | Data dispatcher for task work
`public uint32_t `[`minimum_batch_size`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1aa6d1a8c237e6347a1943127ef750b9da) | Calculated minimum batch size
`public  `[`transient_data_container`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1a68937e8274e6793c8774887a78e20c40)`(size_t _max_data_parallel_workload)` | Initializes a new instance of the base_task<TMemInterface>.transient_container struct.
`public  `[`~transient_data_container`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1a3fdfecd81dd1c61526613cc4606fe0a7)`()` | Finalizes an instance of the base_task<TMemInterface>.transient_container class.

## Members

#### `public `[`data_vector`](#classtask__scheduler_1_1guarded)` `[`data_workload`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1a1ade8d5e1eb8312e998f6cfe3522108d) 

Total number of times work function was called

#### `public `[`data_dispatcher_type`](#classtask__scheduler_1_1lock__free__batch__dispatcher)` * `[`data_dispatcher`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1a52e4c2089b23f0c2f10e7d7afbbc0b11) 

Data dispatcher for task work

#### `public uint32_t `[`minimum_batch_size`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1aa6d1a8c237e6347a1943127ef750b9da) 

Calculated minimum batch size

#### `public  `[`transient_data_container`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1a68937e8274e6793c8774887a78e20c40)`(size_t _max_data_parallel_workload)` 

Initializes a new instance of the base_task<TMemInterface>.transient_container struct.

#### `public  `[`~transient_data_container`](#structtask__scheduler_1_1base__data__task_1_1transient__data__container_1a3fdfecd81dd1c61526613cc4606fe0a7)`()` 

Finalizes an instance of the base_task<TMemInterface>.transient_container class.

Generated by [Moxygen](https://sourcey.com/moxygen)