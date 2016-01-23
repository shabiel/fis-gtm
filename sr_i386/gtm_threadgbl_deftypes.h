#ifdef DEBUG
# define ggo_grabbing_crit 0
# define ggt_grabbing_crit gd_region *
# define ggo_boolchain 4
# define ggt_boolchain triple
# define ggo_boolchain_ptr 76
# define ggt_boolchain_ptr triple *
# define ggo_bool_targ_anchor 80
# define ggt_bool_targ_anchor tbp
# define ggo_bool_targ_ptr 92
# define ggt_bool_targ_ptr tbp *
# define ggo_code_generated 96
# define ggt_code_generated boolean_t
# define ggo_codegen_padlen 100
# define ggt_codegen_padlen int4
# define ggo_compile_time 104
# define ggt_compile_time boolean_t
# define ggo_curtchain 108
# define ggt_curtchain triple *
# define ggo_director_ident 112
# define ggt_director_ident mstr
# define ggo_director_mval 124
# define ggt_director_mval mval
# define ggo_director_token 148
# define ggt_director_token char
# define ggo_dollar_zcstatus 152
# define ggt_dollar_zcstatus int4
# define ggo_expr_depth 156
# define ggt_expr_depth unsigned int
# define ggo_expr_start 160
# define ggt_expr_start triple *
# define ggo_expr_start_orig 164
# define ggt_expr_start_orig triple *
# define ggo_defined_symbols 168
# define ggt_defined_symbols struct sym_table *
# define ggo_for_stack_ptr 172
# define ggt_for_stack_ptr oprtype **
# define ggo_gtm_fullbool 176
# define ggt_gtm_fullbool unsigned int
# define ggo_ind_result 180
# define ggt_ind_result mval *
# define ggo_ind_source 184
# define ggt_ind_source mval *
# define ggo_indirection_mval 188
# define ggt_indirection_mval mval
# define ggo_last_source_column 212
# define ggt_last_source_column int
# define ggo_max_advancewindow_line 216
# define ggt_max_advancewindow_line int4
# define ggo_linkage_first 220
# define ggt_linkage_first struct linkage_entry *
# define ggo_linkage_last 224
# define ggt_linkage_last struct linkage_entry *
# define ggo_pos_in_chain 228
# define ggt_pos_in_chain triple
# define ggo_s2n_intlit 300
# define ggt_s2n_intlit boolean_t
# define ggo_routine_source_offset 304
# define ggt_routine_source_offset uint4
# define ggo_saw_side_effect 308
# define ggt_saw_side_effect boolean_t
# define ggo_shift_side_effects 312
# define ggt_shift_side_effects int
# define ggo_side_effect_base 316
# define ggt_side_effect_base boolean_t *
# define ggo_side_effect_depth 320
# define ggt_side_effect_depth uint4
# define ggo_side_effect_handling 324
# define ggt_side_effect_handling int
# define ggo_source_error_found 328
# define ggt_source_error_found int4
# define ggo_temp_subs 332
# define ggt_temp_subs boolean_t
# define ggo_trigger_compile_and_link 336
# define ggt_trigger_compile_and_link boolean_t
# define ggo_window_ident 340
# define ggt_window_ident mstr
# define ggo_window_mval 352
# define ggt_window_mval mval
# define ggo_window_token 376
# define ggt_window_token char
# define ggo_dbinit_max_hrtbt_delta 380
# define ggt_dbinit_max_hrtbt_delta uint4
# define ggo_dollar_zmaxtptime 384
# define ggt_dollar_zmaxtptime int4
# define ggo_donot_commit 388
# define ggt_donot_commit boolean_t
# define ggo_donot_write_inctn_in_wcs_recover 392
# define ggt_donot_write_inctn_in_wcs_recover boolean_t
# define ggo_gbuff_limit 396
# define ggt_gbuff_limit mval
# define ggo_gd_targ_tn 424
# define ggt_gd_targ_tn trans_num
# define ggo_gd_targ_reg_array 432
# define ggt_gd_targ_reg_array trans_num *
# define ggo_gd_targ_reg_array_size 436
# define ggt_gd_targ_reg_array_size uint4
# define ggo_gd_targ_addr 440
# define ggt_gd_targ_addr gd_addr *
# define ggo_gd_targ_gvnh_reg 444
# define ggt_gd_targ_gvnh_reg gvnh_reg_t *
# define ggo_gd_targ_map 448
# define ggt_gd_targ_map gd_binding *
# define ggo_gtm_custom_errors 452
# define ggt_gtm_custom_errors mstr
# define ggo_gv_extname_size 464
# define ggt_gv_extname_size int4
# define ggo_gv_last_subsc_null 468
# define ggt_gv_last_subsc_null boolean_t
# define ggo_gv_mergekey2 472
# define ggt_gv_mergekey2 gv_key *
# define ggo_gv_reorgkey 476
# define ggt_gv_reorgkey gv_key *
# define ggo_gv_some_subsc_null 480
# define ggt_gv_some_subsc_null boolean_t
# define ggo_gv_sparekey 484
# define ggt_gv_sparekey gv_key *
# define ggo_gv_sparekey_mval 488
# define ggt_gv_sparekey_mval mval
# define ggo_gv_sparekey_size 512
# define ggt_gv_sparekey_size int4
# define ggo_gv_tporigkey_ptr 516
# define ggt_gv_tporigkey_ptr gv_orig_key_array *
# define ggo_gv_tporig_extnam_str 520
# define ggt_gv_tporig_extnam_str mstr
# define ggo_in_gvcst_redo_root_search 532
# define ggt_in_gvcst_redo_root_search boolean_t
# define ggo_in_op_gvget 536
# define ggt_in_op_gvget boolean_t
# define ggo_issue_DBROLLEDBACK_anyways 540
# define ggt_issue_DBROLLEDBACK_anyways boolean_t
# define ggo_last_fnquery_return_subcnt 544
# define ggt_last_fnquery_return_subcnt int
# define ggo_last_fnquery_return_varname 548
# define ggt_last_fnquery_return_varname mval
# define ggo_ok_to_call_wcs_recover 572
# define ggt_ok_to_call_wcs_recover boolean_t
# define ggo_in_gvcst_bmp_mark_free 576
# define ggt_in_gvcst_bmp_mark_free boolean_t
# define ggo_prev_gv_target 580
# define ggt_prev_gv_target gv_namehead *
# define ggo_ready2signal_gvundef 584
# define ggt_ready2signal_gvundef boolean_t
# define ggo_redo_rootsrch_ctxt 592
# define ggt_redo_rootsrch_ctxt redo_root_search_context
# define ggo_semwait2long 1744
# define ggt_semwait2long volatile boolean_t
# define ggo_skip_file_corrupt_check 1748
# define ggt_skip_file_corrupt_check boolean_t
# define ggo_tpnotacidtime 1752
# define ggt_tpnotacidtime int4
# define ggo_tp_restart_count 1756
# define ggt_tp_restart_count uint4
# define ggo_tp_restart_dont_counts 1760
# define ggt_tp_restart_dont_counts int4
# define ggo_tp_restart_entryref 1764
# define ggt_tp_restart_entryref mval
# define ggo_tp_restart_failhist_indx 1788
# define ggt_tp_restart_failhist_indx int4
# define ggo_tprestart_syslog_delta 1792
# define ggt_tprestart_syslog_delta int4
# define ggo_tprestart_syslog_limit 1796
# define ggt_tprestart_syslog_limit int4
# define ggo_transform 1800
# define ggt_transform boolean_t
# define ggo_wcs_recover_done 1804
# define ggt_wcs_recover_done boolean_t
# define ggo_in_op_fnnext 1808
# define ggt_in_op_fnnext boolean_t
# define ggo_local_collseq 1812
# define ggt_local_collseq collseq *
# define ggo_local_collseq_stdnull 1816
# define ggt_local_collseq_stdnull boolean_t
# define ggo_local_coll_nums_as_strings 1820
# define ggt_local_coll_nums_as_strings boolean_t
# define ggo_lv_null_subs 1824
# define ggt_lv_null_subs int
# define ggo_max_lcl_coll_xform_bufsiz 1828
# define ggt_max_lcl_coll_xform_bufsiz int
# define ggo_replgbl 1832
# define ggt_replgbl replgbl_t
# define ggo_tqread_nowait 1856
# define ggt_tqread_nowait boolean_t
# define ggo_arlink_enabled 1860
# define ggt_arlink_enabled boolean_t
# define ggo_arlink_loaded 1864
# define ggt_arlink_loaded uint4
# define ggo_collseq_list 1868
# define ggt_collseq_list collseq *
# define ggo_create_fatal_error_zshow_dmp_fptr 1872
# define ggt_create_fatal_error_zshow_dmp_fptr void
# define gga_create_fatal_error_zshow_dmp_fptr (void)
typedef void (*ggf_create_fatal_error_zshow_dmp_fptr)(void);
# define ggo_disable_sigcont 1876
# define ggt_disable_sigcont boolean_t
# define ggo_dollar_zcompile 1880
# define ggt_dollar_zcompile mstr
# define ggo_dollar_zmode 1892
# define ggt_dollar_zmode mval
# define ggo_dollar_zonlnrlbk 1916
# define ggt_dollar_zonlnrlbk int
# define ggo_dollar_zclose 1920
# define ggt_dollar_zclose int
# define ggo_dollar_zroutines 1924
# define ggt_dollar_zroutines mstr
# define ggo_error_on_jnl_file_lost 1936
# define ggt_error_on_jnl_file_lost unsigned int
# define ggo_fnzsearch_lv_vars 1940
# define ggt_fnzsearch_lv_vars lv_val *
# define ggo_fnzsearch_sub_mval 1944
# define ggt_fnzsearch_sub_mval mval
# define ggo_fnzsearch_nullsubs_sav 1968
# define ggt_fnzsearch_nullsubs_sav int
# define ggo_fnzsearch_globbuf_ptr 1972
# define ggt_fnzsearch_globbuf_ptr glob_t *
# define ggo_glvn_pool_ptr 1976
# define ggt_glvn_pool_ptr glvn_pool *
# define ggo_gtmdbgflags 1980
# define ggt_gtmdbgflags int
# define ggo_gtmdbgflags_freq 1984
# define ggt_gtmdbgflags_freq int
# define ggo_gtmdbgflags_freq_cntr 1988
# define ggt_gtmdbgflags_freq_cntr int
# define ggo_gtm_env_init_started 1992
# define ggt_gtm_env_init_started boolean_t
# define ggo_gtm_env_xlate_entry 1996
# define ggt_gtm_env_xlate_entry int
# define gga_gtm_env_xlate_entry ()
typedef int (*ggf_gtm_env_xlate_entry)();
# define ggo_gtm_environment_init 2000
# define ggt_gtm_environment_init boolean_t
# define ggo_gtm_sigusr1_handler 2004
# define ggt_gtm_sigusr1_handler void
# define gga_gtm_sigusr1_handler (void)
typedef void (*ggf_gtm_sigusr1_handler)(void);
# define ggo_gtm_linktmpdir 2008
# define ggt_gtm_linktmpdir mstr
# define ggo_gtm_trctbl_cur 2020
# define ggt_gtm_trctbl_cur trctbl_entry *
# define ggo_gtm_trctbl_end 2024
# define ggt_gtm_trctbl_end trctbl_entry *
# define ggo_gtm_trctbl_groups 2028
# define ggt_gtm_trctbl_groups unsigned int
# define ggo_gtm_trctbl_start 2032
# define ggt_gtm_trctbl_start trctbl_entry *
# define ggo_gtm_waitstuck_script 2036
# define ggt_gtm_waitstuck_script mstr
# define ggo_gtmprompt 2048
# define ggt_gtmprompt mstr
# define ggo_gtmsecshr_comkey 2060
# define ggt_gtmsecshr_comkey unsigned int
# define ggo_in_zwrite 2064
# define ggt_in_zwrite boolean_t
# define ggo_lab_lnr 2068
# define ggt_lab_lnr lnr_tabent **
# define ggo_jobexam_counter 2072
# define ggt_jobexam_counter unsigned int
# define ggo_lab_proxy 2076
# define ggt_lab_proxy lab_tabent_proxy
# define ggo_mprof_alloc_reclaim 2084
# define ggt_mprof_alloc_reclaim boolean_t
# define ggo_mprof_chunk_avail_size 2088
# define ggt_mprof_chunk_avail_size int
# define ggo_mprof_env_gbl_name 2092
# define ggt_mprof_env_gbl_name mval
# define ggo_mprof_ptr 2116
# define ggt_mprof_ptr mprof_wrapper *
# define ggo_mprof_reclaim_addr 2120
# define ggt_mprof_reclaim_addr char *
# define ggo_mprof_reclaim_cnt 2124
# define ggt_mprof_reclaim_cnt int
# define ggo_mprof_stack_curr_frame 2128
# define ggt_mprof_stack_curr_frame mprof_stack_frame *
# define ggo_mprof_stack_next_frame 2132
# define ggt_mprof_stack_next_frame mprof_stack_frame *
# define ggo_open_shlib_root 2136
# define ggt_open_shlib_root open_shlib *
# define ggo_parm_pool_ptr 2140
# define ggt_parm_pool_ptr parm_pool *
# define ggo_parms_cnt 2144
# define ggt_parms_cnt unsigned int
# define ggo_zpeek_regname 2148
# define ggt_zpeek_regname char
# define ggl_zpeek_regname 31
# define ggo_zpeek_regname_len 2180
# define ggt_zpeek_regname_len int
# define ggo_zpeek_reg_ptr 2184
# define ggt_zpeek_reg_ptr gd_region *
# define ggo_pipefifo_interrupt 2188
# define ggt_pipefifo_interrupt int
# define ggo_prof_fp 2192
# define ggt_prof_fp mprof_stack_frame *
# define ggo_relink_allowed 2196
# define ggt_relink_allowed int
# define ggo_set_zroutines_cycle 2200
# define ggt_set_zroutines_cycle uint4
# define ggo_trans_code_pop 2204
# define ggt_trans_code_pop mval *
# define ggo_view_ydirt_str 2208
# define ggt_view_ydirt_str char *
# define ggo_view_ydirt_str_len 2212
# define ggt_view_ydirt_str_len int4
# define ggo_zdate_form 2216
# define ggt_zdate_form int4
# define ggo_zintcmd_active 2220
# define ggt_zintcmd_active zintcmd_active_info
# define ggl_zintcmd_active 36
# define ggo_zro_root 2256
# define ggt_zro_root zro_ent *
# define ggo_zsearch_var 2260
# define ggt_zsearch_var lv_val *
# define ggo_poll_fds_buffer 2264
# define ggt_poll_fds_buffer char *
# define ggo_poll_fds_buffer_size 2268
# define ggt_poll_fds_buffer_size size_t
# define ggo_socket_handle_counter 2272
# define ggt_socket_handle_counter int
# define ggo_director_string 2276
# define ggt_director_string char
# define ggl_director_string 32
# define ggo_fnpca 2308
# define ggt_fnpca fnpc_area
# define ggo_for_stack 20116
# define ggt_for_stack oprtype *
# define ggl_for_stack 128
# define ggo_for_temps 20244
# define ggt_for_temps boolean_t
# define ggl_for_temps 128
# define ggo_last_fnquery_return_sub 20372
# define ggt_last_fnquery_return_sub mval
# define ggl_last_fnquery_return_sub 768
# define ggo_lcl_coll_xform_buff 21140
# define ggt_lcl_coll_xform_buff char *
# define ggo_protmem_ba 21144
# define ggt_protmem_ba mstr
# define ggo_parm_ary 21156
# define ggt_parm_ary char *
# define ggl_parm_ary 4096
# define ggo_parm_ary_len 25252
# define ggt_parm_ary_len int
# define ggl_parm_ary_len 4096
# define ggo_parm_str_len 29348
# define ggt_parm_str_len int
# define ggl_parm_str_len 4096
# define ggo_prombuf 33444
# define ggt_prombuf char
# define ggl_prombuf 32
# define ggo_tp_restart_failhist_arry 33476
# define ggt_tp_restart_failhist_arry char
# define ggl_tp_restart_failhist_arry 32
# define ggo_window_string 33508
# define ggt_window_string char
# define ggl_window_string 32
# define ggo_tmp_object_file_name 33540
# define ggt_tmp_object_file_name char
# define ggl_tmp_object_file_name 4097
# define ggo_last_va_list_ptr 37640
# define ggt_last_va_list_ptr va_list
# define ggo_util_outbuff 37644
# define ggt_util_outbuff char
# define ggl_util_outbuff 6144
# define ggo_util_outbuff_ptr 43788
# define ggt_util_outbuff_ptr char *
# define ggo_util_outptr 43792
# define ggt_util_outptr char *
# define ggo_callin_hashtab 43796
# define ggt_callin_hashtab hash_table_str *
# define ggo_ci_table 43800
# define ggt_ci_table callin_entry_list *
# define ggo_extcall_package_root 43804
# define ggt_extcall_package_root struct extcall_package_list *
# define ggo_gtmci_nested_level 43808
# define ggt_gtmci_nested_level unsigned int
# define ggo_temp_fgncal_stack 43812
# define ggt_temp_fgncal_stack unsigned char *
# define ggo_midchild_send_locals 43816
# define ggt_midchild_send_locals boolean_t
# define ggo_want_empty_gvts 43820
# define ggt_want_empty_gvts boolean_t
# define ggo_in_mu_swap_root_state 43824
# define ggt_in_mu_swap_root_state unsigned int
# define ggo_prev_t_tries 43828
# define ggt_prev_t_tries unsigned int
# define ggo_rlbk_during_redo_root 43832
# define ggt_rlbk_during_redo_root boolean_t
# define ggo_mlk_yield_pid 43836
# define ggt_mlk_yield_pid uint4
# define ggo_jnl_extract_nocol 43840
# define ggt_jnl_extract_nocol uint4
# define ggo_skip_gtm_putmsg 43844
# define ggt_skip_gtm_putmsg boolean_t
# define ggo_spangbl_seen 43848
# define ggt_spangbl_seen boolean_t
# define ggo_no_spangbls 43852
# define ggt_no_spangbls boolean_t
# define ggo_max_fid_index 43856
# define ggt_max_fid_index int
# define ggo_is_mu_rndwn_rlnkctl 43860
# define ggt_is_mu_rndwn_rlnkctl int
# define ggo_expand_prev_key 43864
# define ggt_expand_prev_key boolean_t
# define ggo_gtm_autorelink_ctlmax 43868
# define ggt_gtm_autorelink_ctlmax uint4
# define ggo_gvt_triggers_read_this_tn 43872
# define ggt_gvt_triggers_read_this_tn boolean_t
# define ggo_op_fntext_tlevel 43876
# define ggt_op_fntext_tlevel uint4
# define ggo_in_op_fntext 43880
# define ggt_in_op_fntext boolean_t
# define ggo_ztrigbuff 43884
# define ggt_ztrigbuff char *
# define ggo_ztrigbuffAllocLen 43888
# define ggt_ztrigbuffAllocLen int
# define ggo_ztrigbuffLen 43892
# define ggt_ztrigbuffLen int
# define ggo_ztrig_use_io_curr_device 43896
# define ggt_ztrig_use_io_curr_device boolean_t
# define ggo_continue_proc_cnt 43900
# define ggt_continue_proc_cnt int
# define ggo_gtm_test_fake_enospc 43904
# define ggt_gtm_test_fake_enospc boolean_t
# define ggo_gtm_usesecshr 43908
# define ggt_gtm_usesecshr boolean_t
# define ggo_rts_error_unusable 43912
# define ggt_rts_error_unusable boolean_t
# define ggo_rts_error_unusable_seen 43916
# define ggt_rts_error_unusable_seen boolean_t
# define ggo_trans_restart_hist_array 43920
# define ggt_trans_restart_hist_array trans_restart_hist_t
# define ggl_trans_restart_hist_array 16384
# define ggo_trans_restart_hist_index 60304
# define ggt_trans_restart_hist_index uint4
# define ggo_skip_mv_num_approx_assert 60308
# define ggt_skip_mv_num_approx_assert boolean_t
# define ggo_gtm_gvundef_fatal 60312
# define ggt_gtm_gvundef_fatal boolean_t
# define ggo_gtm_dirtree_collhdr_always 60316
# define ggt_gtm_dirtree_collhdr_always boolean_t
# define ggo_activelv_cycle 60320
# define ggt_activelv_cycle int
# define ggo_activelv_index 60324
# define ggt_activelv_index int
# define ggo_activelv_dbg_array 60328
# define ggt_activelv_dbg_array activelv_dbg_t *
# define ggo_cli_get_str_max_len 60332
# define ggt_cli_get_str_max_len uint4
# define ggo_gtmio_skip_tlevel_assert 60336
# define ggt_gtmio_skip_tlevel_assert boolean_t
# define ggo_in_trigger_upgrade 60340
# define ggt_in_trigger_upgrade boolean_t
# define ggo_gtm_test_autorelink_always 60344
# define ggt_gtm_test_autorelink_always boolean_t
# define ggo_fork_without_child_wait 60348
# define ggt_fork_without_child_wait boolean_t
# define size_gtm_threadgbl_struct 60352
#else
# define ggo_grabbing_crit 0
# define ggt_grabbing_crit gd_region *
# define ggo_boolchain 4
# define ggt_boolchain triple
# define ggo_boolchain_ptr 76
# define ggt_boolchain_ptr triple *
# define ggo_bool_targ_anchor 80
# define ggt_bool_targ_anchor tbp
# define ggo_bool_targ_ptr 92
# define ggt_bool_targ_ptr tbp *
# define ggo_code_generated 96
# define ggt_code_generated boolean_t
# define ggo_codegen_padlen 100
# define ggt_codegen_padlen int4
# define ggo_compile_time 104
# define ggt_compile_time boolean_t
# define ggo_curtchain 108
# define ggt_curtchain triple *
# define ggo_director_ident 112
# define ggt_director_ident mstr
# define ggo_director_mval 124
# define ggt_director_mval mval
# define ggo_director_token 148
# define ggt_director_token char
# define ggo_dollar_zcstatus 152
# define ggt_dollar_zcstatus int4
# define ggo_expr_depth 156
# define ggt_expr_depth unsigned int
# define ggo_expr_start 160
# define ggt_expr_start triple *
# define ggo_expr_start_orig 164
# define ggt_expr_start_orig triple *
# define ggo_defined_symbols 168
# define ggt_defined_symbols struct sym_table *
# define ggo_for_stack_ptr 172
# define ggt_for_stack_ptr oprtype **
# define ggo_gtm_fullbool 176
# define ggt_gtm_fullbool unsigned int
# define ggo_ind_result 180
# define ggt_ind_result mval *
# define ggo_ind_source 184
# define ggt_ind_source mval *
# define ggo_indirection_mval 188
# define ggt_indirection_mval mval
# define ggo_last_source_column 212
# define ggt_last_source_column int
# define ggo_max_advancewindow_line 216
# define ggt_max_advancewindow_line int4
# define ggo_linkage_first 220
# define ggt_linkage_first struct linkage_entry *
# define ggo_linkage_last 224
# define ggt_linkage_last struct linkage_entry *
# define ggo_pos_in_chain 228
# define ggt_pos_in_chain triple
# define ggo_s2n_intlit 300
# define ggt_s2n_intlit boolean_t
# define ggo_routine_source_offset 304
# define ggt_routine_source_offset uint4
# define ggo_saw_side_effect 308
# define ggt_saw_side_effect boolean_t
# define ggo_shift_side_effects 312
# define ggt_shift_side_effects int
# define ggo_side_effect_base 316
# define ggt_side_effect_base boolean_t *
# define ggo_side_effect_depth 320
# define ggt_side_effect_depth uint4
# define ggo_side_effect_handling 324
# define ggt_side_effect_handling int
# define ggo_source_error_found 328
# define ggt_source_error_found int4
# define ggo_temp_subs 332
# define ggt_temp_subs boolean_t
# define ggo_trigger_compile_and_link 336
# define ggt_trigger_compile_and_link boolean_t
# define ggo_window_ident 340
# define ggt_window_ident mstr
# define ggo_window_mval 352
# define ggt_window_mval mval
# define ggo_window_token 376
# define ggt_window_token char
# define ggo_dbinit_max_hrtbt_delta 380
# define ggt_dbinit_max_hrtbt_delta uint4
# define ggo_dollar_zmaxtptime 384
# define ggt_dollar_zmaxtptime int4
# define ggo_donot_commit 388
# define ggt_donot_commit boolean_t
# define ggo_donot_write_inctn_in_wcs_recover 392
# define ggt_donot_write_inctn_in_wcs_recover boolean_t
# define ggo_gbuff_limit 396
# define ggt_gbuff_limit mval
# define ggo_gd_targ_tn 424
# define ggt_gd_targ_tn trans_num
# define ggo_gd_targ_reg_array 432
# define ggt_gd_targ_reg_array trans_num *
# define ggo_gd_targ_reg_array_size 436
# define ggt_gd_targ_reg_array_size uint4
# define ggo_gd_targ_addr 440
# define ggt_gd_targ_addr gd_addr *
# define ggo_gd_targ_gvnh_reg 444
# define ggt_gd_targ_gvnh_reg gvnh_reg_t *
# define ggo_gd_targ_map 448
# define ggt_gd_targ_map gd_binding *
# define ggo_gtm_custom_errors 452
# define ggt_gtm_custom_errors mstr
# define ggo_gv_extname_size 464
# define ggt_gv_extname_size int4
# define ggo_gv_last_subsc_null 468
# define ggt_gv_last_subsc_null boolean_t
# define ggo_gv_mergekey2 472
# define ggt_gv_mergekey2 gv_key *
# define ggo_gv_reorgkey 476
# define ggt_gv_reorgkey gv_key *
# define ggo_gv_some_subsc_null 480
# define ggt_gv_some_subsc_null boolean_t
# define ggo_gv_sparekey 484
# define ggt_gv_sparekey gv_key *
# define ggo_gv_sparekey_mval 488
# define ggt_gv_sparekey_mval mval
# define ggo_gv_sparekey_size 512
# define ggt_gv_sparekey_size int4
# define ggo_gv_tporigkey_ptr 516
# define ggt_gv_tporigkey_ptr gv_orig_key_array *
# define ggo_gv_tporig_extnam_str 520
# define ggt_gv_tporig_extnam_str mstr
# define ggo_in_gvcst_redo_root_search 532
# define ggt_in_gvcst_redo_root_search boolean_t
# define ggo_in_op_gvget 536
# define ggt_in_op_gvget boolean_t
# define ggo_issue_DBROLLEDBACK_anyways 540
# define ggt_issue_DBROLLEDBACK_anyways boolean_t
# define ggo_last_fnquery_return_subcnt 544
# define ggt_last_fnquery_return_subcnt int
# define ggo_last_fnquery_return_varname 548
# define ggt_last_fnquery_return_varname mval
# define ggo_ok_to_call_wcs_recover 572
# define ggt_ok_to_call_wcs_recover boolean_t
# define ggo_in_gvcst_bmp_mark_free 576
# define ggt_in_gvcst_bmp_mark_free boolean_t
# define ggo_prev_gv_target 580
# define ggt_prev_gv_target gv_namehead *
# define ggo_ready2signal_gvundef 584
# define ggt_ready2signal_gvundef boolean_t
# define ggo_redo_rootsrch_ctxt 592
# define ggt_redo_rootsrch_ctxt redo_root_search_context
# define ggo_semwait2long 1704
# define ggt_semwait2long volatile boolean_t
# define ggo_skip_file_corrupt_check 1708
# define ggt_skip_file_corrupt_check boolean_t
# define ggo_tpnotacidtime 1712
# define ggt_tpnotacidtime int4
# define ggo_tp_restart_count 1716
# define ggt_tp_restart_count uint4
# define ggo_tp_restart_dont_counts 1720
# define ggt_tp_restart_dont_counts int4
# define ggo_tp_restart_entryref 1724
# define ggt_tp_restart_entryref mval
# define ggo_tp_restart_failhist_indx 1748
# define ggt_tp_restart_failhist_indx int4
# define ggo_tprestart_syslog_delta 1752
# define ggt_tprestart_syslog_delta int4
# define ggo_tprestart_syslog_limit 1756
# define ggt_tprestart_syslog_limit int4
# define ggo_transform 1760
# define ggt_transform boolean_t
# define ggo_wcs_recover_done 1764
# define ggt_wcs_recover_done boolean_t
# define ggo_in_op_fnnext 1768
# define ggt_in_op_fnnext boolean_t
# define ggo_local_collseq 1772
# define ggt_local_collseq collseq *
# define ggo_local_collseq_stdnull 1776
# define ggt_local_collseq_stdnull boolean_t
# define ggo_local_coll_nums_as_strings 1780
# define ggt_local_coll_nums_as_strings boolean_t
# define ggo_lv_null_subs 1784
# define ggt_lv_null_subs int
# define ggo_max_lcl_coll_xform_bufsiz 1788
# define ggt_max_lcl_coll_xform_bufsiz int
# define ggo_replgbl 1792
# define ggt_replgbl replgbl_t
# define ggo_tqread_nowait 1816
# define ggt_tqread_nowait boolean_t
# define ggo_arlink_enabled 1820
# define ggt_arlink_enabled boolean_t
# define ggo_arlink_loaded 1824
# define ggt_arlink_loaded uint4
# define ggo_collseq_list 1828
# define ggt_collseq_list collseq *
# define ggo_create_fatal_error_zshow_dmp_fptr 1832
# define ggt_create_fatal_error_zshow_dmp_fptr void
# define gga_create_fatal_error_zshow_dmp_fptr (void)
typedef void (*ggf_create_fatal_error_zshow_dmp_fptr)(void);
# define ggo_disable_sigcont 1836
# define ggt_disable_sigcont boolean_t
# define ggo_dollar_zcompile 1840
# define ggt_dollar_zcompile mstr
# define ggo_dollar_zmode 1852
# define ggt_dollar_zmode mval
# define ggo_dollar_zonlnrlbk 1876
# define ggt_dollar_zonlnrlbk int
# define ggo_dollar_zclose 1880
# define ggt_dollar_zclose int
# define ggo_dollar_zroutines 1884
# define ggt_dollar_zroutines mstr
# define ggo_error_on_jnl_file_lost 1896
# define ggt_error_on_jnl_file_lost unsigned int
# define ggo_fnzsearch_lv_vars 1900
# define ggt_fnzsearch_lv_vars lv_val *
# define ggo_fnzsearch_sub_mval 1904
# define ggt_fnzsearch_sub_mval mval
# define ggo_fnzsearch_nullsubs_sav 1928
# define ggt_fnzsearch_nullsubs_sav int
# define ggo_fnzsearch_globbuf_ptr 1932
# define ggt_fnzsearch_globbuf_ptr glob_t *
# define ggo_glvn_pool_ptr 1936
# define ggt_glvn_pool_ptr glvn_pool *
# define ggo_gtm_env_init_started 1940
# define ggt_gtm_env_init_started boolean_t
# define ggo_gtm_env_xlate_entry 1944
# define ggt_gtm_env_xlate_entry int
# define gga_gtm_env_xlate_entry ()
typedef int (*ggf_gtm_env_xlate_entry)();
# define ggo_gtm_environment_init 1948
# define ggt_gtm_environment_init boolean_t
# define ggo_gtm_sigusr1_handler 1952
# define ggt_gtm_sigusr1_handler void
# define gga_gtm_sigusr1_handler (void)
typedef void (*ggf_gtm_sigusr1_handler)(void);
# define ggo_gtm_linktmpdir 1956
# define ggt_gtm_linktmpdir mstr
# define ggo_gtm_trctbl_cur 1968
# define ggt_gtm_trctbl_cur trctbl_entry *
# define ggo_gtm_trctbl_end 1972
# define ggt_gtm_trctbl_end trctbl_entry *
# define ggo_gtm_trctbl_groups 1976
# define ggt_gtm_trctbl_groups unsigned int
# define ggo_gtm_trctbl_start 1980
# define ggt_gtm_trctbl_start trctbl_entry *
# define ggo_gtm_waitstuck_script 1984
# define ggt_gtm_waitstuck_script mstr
# define ggo_gtmprompt 1996
# define ggt_gtmprompt mstr
# define ggo_gtmsecshr_comkey 2008
# define ggt_gtmsecshr_comkey unsigned int
# define ggo_in_zwrite 2012
# define ggt_in_zwrite boolean_t
# define ggo_lab_lnr 2016
# define ggt_lab_lnr lnr_tabent **
# define ggo_jobexam_counter 2020
# define ggt_jobexam_counter unsigned int
# define ggo_lab_proxy 2024
# define ggt_lab_proxy lab_tabent_proxy
# define ggo_mprof_alloc_reclaim 2032
# define ggt_mprof_alloc_reclaim boolean_t
# define ggo_mprof_chunk_avail_size 2036
# define ggt_mprof_chunk_avail_size int
# define ggo_mprof_env_gbl_name 2040
# define ggt_mprof_env_gbl_name mval
# define ggo_mprof_ptr 2064
# define ggt_mprof_ptr mprof_wrapper *
# define ggo_mprof_reclaim_addr 2068
# define ggt_mprof_reclaim_addr char *
# define ggo_mprof_reclaim_cnt 2072
# define ggt_mprof_reclaim_cnt int
# define ggo_mprof_stack_curr_frame 2076
# define ggt_mprof_stack_curr_frame mprof_stack_frame *
# define ggo_mprof_stack_next_frame 2080
# define ggt_mprof_stack_next_frame mprof_stack_frame *
# define ggo_open_shlib_root 2084
# define ggt_open_shlib_root open_shlib *
# define ggo_parm_pool_ptr 2088
# define ggt_parm_pool_ptr parm_pool *
# define ggo_parms_cnt 2092
# define ggt_parms_cnt unsigned int
# define ggo_zpeek_regname 2096
# define ggt_zpeek_regname char
# define ggl_zpeek_regname 31
# define ggo_zpeek_regname_len 2128
# define ggt_zpeek_regname_len int
# define ggo_zpeek_reg_ptr 2132
# define ggt_zpeek_reg_ptr gd_region *
# define ggo_pipefifo_interrupt 2136
# define ggt_pipefifo_interrupt int
# define ggo_prof_fp 2140
# define ggt_prof_fp mprof_stack_frame *
# define ggo_relink_allowed 2144
# define ggt_relink_allowed int
# define ggo_set_zroutines_cycle 2148
# define ggt_set_zroutines_cycle uint4
# define ggo_trans_code_pop 2152
# define ggt_trans_code_pop mval *
# define ggo_view_ydirt_str 2156
# define ggt_view_ydirt_str char *
# define ggo_view_ydirt_str_len 2160
# define ggt_view_ydirt_str_len int4
# define ggo_zdate_form 2164
# define ggt_zdate_form int4
# define ggo_zintcmd_active 2168
# define ggt_zintcmd_active zintcmd_active_info
# define ggl_zintcmd_active 36
# define ggo_zro_root 2204
# define ggt_zro_root zro_ent *
# define ggo_zsearch_var 2208
# define ggt_zsearch_var lv_val *
# define ggo_poll_fds_buffer 2212
# define ggt_poll_fds_buffer char *
# define ggo_poll_fds_buffer_size 2216
# define ggt_poll_fds_buffer_size size_t
# define ggo_socket_handle_counter 2220
# define ggt_socket_handle_counter int
# define ggo_director_string 2224
# define ggt_director_string char
# define ggl_director_string 32
# define ggo_fnpca 2256
# define ggt_fnpca fnpc_area
# define ggo_for_stack 20064
# define ggt_for_stack oprtype *
# define ggl_for_stack 128
# define ggo_for_temps 20192
# define ggt_for_temps boolean_t
# define ggl_for_temps 128
# define ggo_last_fnquery_return_sub 20320
# define ggt_last_fnquery_return_sub mval
# define ggl_last_fnquery_return_sub 768
# define ggo_lcl_coll_xform_buff 21088
# define ggt_lcl_coll_xform_buff char *
# define ggo_protmem_ba 21092
# define ggt_protmem_ba mstr
# define ggo_parm_ary 21104
# define ggt_parm_ary char *
# define ggl_parm_ary 4096
# define ggo_parm_ary_len 25200
# define ggt_parm_ary_len int
# define ggl_parm_ary_len 4096
# define ggo_parm_str_len 29296
# define ggt_parm_str_len int
# define ggl_parm_str_len 4096
# define ggo_prombuf 33392
# define ggt_prombuf char
# define ggl_prombuf 32
# define ggo_tp_restart_failhist_arry 33424
# define ggt_tp_restart_failhist_arry char
# define ggl_tp_restart_failhist_arry 32
# define ggo_window_string 33456
# define ggt_window_string char
# define ggl_window_string 32
# define ggo_tmp_object_file_name 33488
# define ggt_tmp_object_file_name char
# define ggl_tmp_object_file_name 4097
# define ggo_last_va_list_ptr 37588
# define ggt_last_va_list_ptr va_list
# define ggo_util_outbuff 37592
# define ggt_util_outbuff char
# define ggl_util_outbuff 6144
# define ggo_util_outbuff_ptr 43736
# define ggt_util_outbuff_ptr char *
# define ggo_util_outptr 43740
# define ggt_util_outptr char *
# define ggo_callin_hashtab 43744
# define ggt_callin_hashtab hash_table_str *
# define ggo_ci_table 43748
# define ggt_ci_table callin_entry_list *
# define ggo_extcall_package_root 43752
# define ggt_extcall_package_root struct extcall_package_list *
# define ggo_gtmci_nested_level 43756
# define ggt_gtmci_nested_level unsigned int
# define ggo_temp_fgncal_stack 43760
# define ggt_temp_fgncal_stack unsigned char *
# define ggo_midchild_send_locals 43764
# define ggt_midchild_send_locals boolean_t
# define ggo_want_empty_gvts 43768
# define ggt_want_empty_gvts boolean_t
# define ggo_in_mu_swap_root_state 43772
# define ggt_in_mu_swap_root_state unsigned int
# define ggo_prev_t_tries 43776
# define ggt_prev_t_tries unsigned int
# define ggo_rlbk_during_redo_root 43780
# define ggt_rlbk_during_redo_root boolean_t
# define ggo_mlk_yield_pid 43784
# define ggt_mlk_yield_pid uint4
# define ggo_jnl_extract_nocol 43788
# define ggt_jnl_extract_nocol uint4
# define ggo_skip_gtm_putmsg 43792
# define ggt_skip_gtm_putmsg boolean_t
# define ggo_spangbl_seen 43796
# define ggt_spangbl_seen boolean_t
# define ggo_no_spangbls 43800
# define ggt_no_spangbls boolean_t
# define ggo_max_fid_index 43804
# define ggt_max_fid_index int
# define ggo_is_mu_rndwn_rlnkctl 43808
# define ggt_is_mu_rndwn_rlnkctl int
# define ggo_expand_prev_key 43812
# define ggt_expand_prev_key boolean_t
# define ggo_gtm_autorelink_ctlmax 43816
# define ggt_gtm_autorelink_ctlmax uint4
# define ggo_gvt_triggers_read_this_tn 43820
# define ggt_gvt_triggers_read_this_tn boolean_t
# define ggo_op_fntext_tlevel 43824
# define ggt_op_fntext_tlevel uint4
# define ggo_in_op_fntext 43828
# define ggt_in_op_fntext boolean_t
# define ggo_ztrigbuff 43832
# define ggt_ztrigbuff char *
# define ggo_ztrigbuffAllocLen 43836
# define ggt_ztrigbuffAllocLen int
# define ggo_ztrigbuffLen 43840
# define ggt_ztrigbuffLen int
# define ggo_ztrig_use_io_curr_device 43844
# define ggt_ztrig_use_io_curr_device boolean_t
# define size_gtm_threadgbl_struct 43848
#endif
