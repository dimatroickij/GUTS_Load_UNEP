VerifyCADES_UNEP_withSignedReport()
{
	web_cache_cleanup();
	web_cleanup_auto_headers();
	web_cleanup_cookies();

	lr_output_message(	lr_eval_string("{dataPath}/{VerifyCADES_withSignedReport_file}"));
	lr_read_file(lr_eval_string("{dataPath}/{VerifyCADES_withSignedReport_file}"), "request", 0);

	lr_output_message("Use file: {VerifyCADES_withSignedReport_file}");
	
	lr_continue_on_error(1);

	lr_start_transaction("VerifyCADES_withSignedReport");
	soap_request("StepName=VerifyCADES_withSignedReport",
		"URL={URL}",
		"SOAPEnvelope="
			"{request}",
		"ExpectedResponse=AnySoap",
		"ResponseParam=result",
		LAST);

	//lr_output_message("log/result: %s", lr_eval_string("{result}"));
	if(strstr( lr_eval_string("{result}"), lr_eval_string("{VerifyCADES_withSignedReport_response}"))==NULL)
	{
        lr_end_transaction("VerifyCADES_withSignedReport", LR_FAIL);
		lr_output_message( lr_eval_string("error: expected contains {VerifyCADES_withSignedReport_response}, but got {result}"));
	}
	else
	{
		lr_end_transaction("VerifyCADES_withSignedReport", LR_PASS);
	}
    
    lr_continue_on_error(0);
	return 0;
}
