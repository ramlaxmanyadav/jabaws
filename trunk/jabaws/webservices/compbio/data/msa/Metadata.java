package compbio.data.msa;

import javax.jws.WebParam;

import compbio.metadata.Limit;
import compbio.metadata.LimitsManager;
import compbio.metadata.PresetManager;
import compbio.metadata.RunnerConfig;

public interface Metadata<T> {

	/**
	 * Get options supported by a web service
	 * 
	 * @return RunnerConfig the list of options and parameters supported by a
	 *         web service.
	 */
	RunnerConfig<T> getRunnerOptions();

	/**
	 * Get presets supported by a web service
	 * 
	 * @return PresetManager the object contains information about presets
	 *         supported by a web service
	 */
	PresetManager<T> getPresets();

	/**
	 * Get a Limit for a preset.
	 * 
	 * @param presetName
	 *            the name of the preset. if no name is provided, then the
	 *            default preset is returned. If no limit for a particular
	 *            preset is defined then the default preset is returned
	 * @return Limit
	 */
	Limit<T> getLimit(@WebParam(name = "presetName") String presetName);

	/**
	 * List Limits supported by a web service.
	 * 
	 * @return LimitManager
	 */
	LimitsManager<T> getLimits();

}
