VerifyXAdES_UNEP_simple()
{
	web_cache_cleanup();
	web_cleanup_auto_headers();
	web_cleanup_cookies();

	lr_output_message(	lr_eval_string("{dataPath}/{VerifyXAdES_simple_file}"));
	lr_read_file(lr_eval_string("{dataPath}/{VerifyXAdES_simple_file}"), "request", 0);

	lr_output_message("Use file: {VerifyXAdES_simple_file}");

	lr_continue_on_error(1);
	
	lr_start_transaction("VerifyXAdES_UNEP_simple");
	soap_request("StepName=VerifyXAdES_UNEP_simple",
		"URL={URL}",
		"SOAPEnvelope="
			"{request}",
		"ExpectedResponse=AnySoap",
		"ResponseParam=result",
		LAST);

	//lr_output_message("log/result: %s", lr_eval_string("{result}"));
	if(strstr( lr_eval_string("{result}"), lr_eval_string("{VerifyXAdES_simple_response}"))==NULL)
	{
        lr_end_transaction("VerifyXAdES_UNEP_simple", LR_FAIL);
		lr_output_message( lr_eval_string("error: expected contains {VerifyXAdES_simple_response}, but got {result}"));
	}
	else
	{
		lr_end_transaction("VerifyXAdES_UNEP_simple", LR_PASS);
	}
	
	lr_continue_on_error(0);
	return 0;
}
