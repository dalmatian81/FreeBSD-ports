--- chrome/browser/task_manager/sampling/task_group.cc.orig	2017-02-02 02:02:49 UTC
+++ chrome/browser/task_manager/sampling/task_group.cc
@@ -25,9 +25,9 @@ const int kBackgroundRefreshTypesMask =
     REFRESH_TYPE_CPU |
     REFRESH_TYPE_MEMORY |
     REFRESH_TYPE_IDLE_WAKEUPS |
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
     REFRESH_TYPE_FD_COUNT |
-#endif  // defined(OS_LINUX)
+#endif  // defined(OS_LINUX) || defined(OS_BSD)
     REFRESH_TYPE_PRIORITY;
 
 #if defined(OS_WIN)
@@ -88,9 +88,9 @@ TaskGroup::TaskGroup(
       nacl_debug_stub_port_(-1),
 #endif  // !defined(DISABLE_NACL)
       idle_wakeups_per_second_(-1),
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
       open_fd_count_(-1),
-#endif  // defined(OS_LINUX)
+#endif  // defined(OS_LINUX) || defined(OS_BSD)
       gpu_memory_has_duplicates_(false),
       is_backgrounded_(false),
       weak_ptr_factory_(this) {
@@ -103,10 +103,10 @@ TaskGroup::TaskGroup(
                                       weak_ptr_factory_.GetWeakPtr()),
                            base::Bind(&TaskGroup::OnIdleWakeupsRefreshDone,
                                       weak_ptr_factory_.GetWeakPtr()),
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
                            base::Bind(&TaskGroup::OnOpenFdCountRefreshDone,
                                       weak_ptr_factory_.GetWeakPtr()),
-#endif  // defined(OS_LINUX)
+#endif  // defined(OS_LINUX) || defined(OS_BSD)
                            base::Bind(&TaskGroup::OnProcessPriorityDone,
                                       weak_ptr_factory_.GetWeakPtr())));
   worker_thread_sampler_.swap(sampler);
@@ -282,14 +282,14 @@ void TaskGroup::OnIdleWakeupsRefreshDone
   OnBackgroundRefreshTypeFinished(REFRESH_TYPE_IDLE_WAKEUPS);
 }
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
 void TaskGroup::OnOpenFdCountRefreshDone(int open_fd_count) {
   DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
 
   open_fd_count_ = open_fd_count;
   OnBackgroundRefreshTypeFinished(REFRESH_TYPE_FD_COUNT);
 }
-#endif  // defined(OS_LINUX)
+#endif  // defined(OS_LINUX) || defined(OS_BSD)
 
 void TaskGroup::OnProcessPriorityDone(bool is_backgrounded) {
   DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
